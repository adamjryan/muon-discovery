/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServiceDescriptorServer.h
 * Author: adam
 *
 * Created on 22 January 2017, 12:57
 */

#ifndef SERVICEDESCRIPTORSERVER_H
#define SERVICEDESCRIPTORSERVER_H

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "io/muoncore/discovery/ServiceDescriptor.h"

class ServiceDescriptorServer
{
public:
    enum MessageType{
        SERVICE_DESCRIPTOR_REQUEST,
        SERVICE_DESCRIPTOR_RESPONSE,
        SERVICE_STARTED,
        SERVICE_STOPPED,
    };
public:
    static const char* MULTICAST_ADDRESS;
    static const int PORT = 9898;
    static const long MAX_TRANSMIT_INTERVAL = 5000;
    
private:
    std::mutex mutex;
    std::thread thread;
//    std::thread listeningThread;
    std::condition_variable semaphore;
    bool ready = false;
    bool enabled = false;
    /*volatile needed?*/ ServiceDescriptor* serviceDescriptor = nullptr;
    std::vector<ServiceDescriptor*> foundServices;
    
public:
    static int newUdpMulticastSocket( const char* ipAddress, uint16_t port )
    {
        int socketFd = newUdpSocket();
        u_int TRUE = 1;
        if( setsockopt( socketFd, SOL_SOCKET, SO_REUSEADDR, &TRUE, sizeof(TRUE) ) < 0 ){
            perror("socket");
            exit(EXIT_FAILURE);
        }

        struct sockaddr_in listeningAddress;
        listeningAddress.sin_family = AF_INET;
        listeningAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        listeningAddress.sin_port = htons(port);
        if( bind( socketFd, (struct sockaddr *)&listeningAddress, sizeof(listeningAddress) ) < 0 ){
            perror("socket");
            exit(EXIT_FAILURE);
        }

        struct ip_mreq multicastAddress;
        multicastAddress.imr_multiaddr.s_addr = inet_addr(ipAddress);
        multicastAddress.imr_interface.s_addr = htonl(INADDR_ANY);
        if(  setsockopt( socketFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicastAddress, sizeof(multicastAddress) ) < 0 ){
            perror("socket");
            exit(EXIT_FAILURE);
        }
        return socketFd;
    }

    ServiceDescriptorServer()
    :   thread( ServiceDescriptorServer::run1, this )
//    :   listeningThread( listenForBroadcastsWith, this )
    {
    }

    void setServiceDescriptor( ServiceDescriptor* serviceDescriptor )
    {
        this->serviceDescriptor = serviceDescriptor;
    }

    void setEnabled( bool enabled )
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            this->enabled = enabled;
            mutex.unlock();
        }
        semaphore.notify_one();
    }

//    void pollForService()
//    {
//        //TODO makes request for particular service type to which only these services will make responses.
//        //Continue polling at a specified interval until a reply for the given service is received. If service already is cached then return that one.
//    }
//
//    vector<ServiceDescriptor*>* getServices( bool refreshCache )
//    {
//        if( refreshCache ){
//            std::string serviceDescritorRequest =
//            "{"
//                "messageType: 0"
//            "}";
//            sendUdp( MulticastDiscovery::MULTICAST_ADDRESS, MulticastDiscovery::PORT, serviceDescritorRequest.c_str(), serviceDescritorRequest.length() );
//        }
//        return &foundServices;
//    }
    
private:
    void run()
    {
        std::auto_ptr<avro::OutputStream> outputStream = avro::memoryOutputStream(1);
        avro::EncoderPtr binaryEncoderPtr = avro::binaryEncoder();
        binaryEncoderPtr->init(*outputStream);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
        while( true ){
            std::unique_lock<std::mutex> lock(mutex);
            semaphore.wait( lock, [this]{ return enabled; } );
            while( enabled ){
                std::this_thread::sleep_until( std::chrono::system_clock::now() += std::chrono::seconds(5) );
                if( serviceDescriptor != nullptr ){
                    size_t dataLength = outputStream->byteCount();
                    outputStream->backup(dataLength);
                    avro::encode( *binaryEncoderPtr, serviceDescriptor->serviceDescriptorSer );
                    outputStream->flush();
                    dataLength = outputStream->byteCount();
                    uint8_t data[dataLength];
                    uint8_t* dataPtr = data;
                    std::auto_ptr<avro::InputStream> inputStream = avro::memoryInputStream(*outputStream);
                    avro::StreamReader streamReader(*inputStream);
                    while( streamReader.hasMore() ){
                        *dataPtr++ = streamReader.read();
                    }
                    sendUdp( MULTICAST_ADDRESS, PORT, data, dataLength );
                }
            }
        }
#pragma clang diagnostic pop
    }
    
    void listenForBroadcasts()
    {
        while( true ){
            std::unique_lock<std::mutex> lock(mutex);
            semaphore.wait( lock, [this]{ return enabled; } );
            int socketFd = newUdpMulticastSocket( MULTICAST_ADDRESS, PORT );
            uint8_t buffer[100];
            sockaddr_in sockAddrIn;
            socklen_t sizeOfSockAddrIn = sizeof(sockAddrIn);
            while( enabled ){
                /*ssize_t result =*/ recvfrom( socketFd, buffer, sizeof(buffer), 0, (struct sockaddr*)&sockAddrIn, &sizeOfSockAddrIn );
                switch( translateMessage() ){
                case SERVICE_DESCRIPTOR_REQUEST:
                    broadcastServiceDescriptor();
                    break;
                case SERVICE_DESCRIPTOR_RESPONSE:
                    cacheServiceDescriptor();
                    break;
                case SERVICE_STARTED:
                    break;
                case SERVICE_STOPPED:
                    break;
                }
            }
            shutdown( socketFd, 2 );
        }
    }
    
    MessageType translateMessage()
    {
        return MessageType::SERVICE_DESCRIPTOR_REQUEST;
    }
    
    void broadcastServiceDescriptor()
    {
        
    }
    
    void cacheServiceDescriptor()
    {
        ServiceDescriptor* serviceDescriptor = new ServiceDescriptor( "" );
        foundServices.push_back(serviceDescriptor);
    }
    
    void sendUdp( const char* ipAddress, uint16_t port, const void* data, ssize_t dataLength )
    {
        int socketFd = newUdpSocket();
        struct sockaddr_in targetSocketAddress;
        targetSocketAddress.sin_family = AF_INET;
        targetSocketAddress.sin_addr.s_addr = inet_addr(ipAddress);
        targetSocketAddress.sin_port = htons(port);
        sendto( socketFd, data, dataLength, 0, (struct sockaddr *)&targetSocketAddress, sizeof(targetSocketAddress) );
        shutdown( socketFd, 2 );
    }
    
    static int newUdpSocket()
    {
        int socketFd = socket( AF_INET, SOCK_DGRAM, 0 );
        if( socketFd < 0 ){
            perror("socket");
            exit(EXIT_FAILURE);
        }
        return socketFd;
    }

    static void run1( ServiceDescriptorServer* serviceDescriptorServer )
    {
        serviceDescriptorServer->run();
    }

    static void listenForBroadcastsWith( ServiceDescriptorServer* serviceDescriptorServer )
    {
        serviceDescriptorServer->listenForBroadcasts();
    }
};

#endif /* SERVICEDESCRIPTORSERVER_H */