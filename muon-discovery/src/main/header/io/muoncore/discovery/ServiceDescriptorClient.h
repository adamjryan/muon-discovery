//
// Created by adam on 19/05/17.
//

#ifndef MUON_DISCOVERY_SERVICEDESCRIPTORCLIENT_H
#define MUON_DISCOVERY_SERVICEDESCRIPTORCLIENT_H

#include <thread>
#include <map>
#include "io/muoncore/discovery/ServiceDescriptorServer.h"

class ServiceDescriptorClient
{
public:
    class ServiceCache
    {
        friend class ServiceDescriptorClient;
    private:
        std::map<std::string,std::pair<ServiceDescriptor*,long>> serviceCache;

    public:
        void getServices( std::vector<ServiceDescriptor*>* serviceDescriptors )
        {
            for( std::map<std::string,std::pair<ServiceDescriptor*,long>>::iterator iterator = serviceCache.begin(); iterator != serviceCache.end(); ++iterator ){
                if( iterator->second.second + ServiceDescriptorServer::MAX_TRANSMIT_INTERVAL - std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch() ).count() < 1 ){
                    serviceCache.erase(iterator->first);
                    continue;
                }
                serviceDescriptors->push_back(iterator->second.first);
            }
        }

    private:
        ServiceCache(){}

        void addService( ServiceDescriptor* serviceDescriptor )
        {

            serviceCache[ serviceDescriptor->getIdentifier() ] = std::pair<ServiceDescriptor*,long>(
                serviceDescriptor,
                std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch() ).count()
            );
        }
    };

private:
    ServiceCache serviceCache;
    std::mutex mutex;
    std::thread thread;
    std::condition_variable semaphore;
    bool enabled = false;

public:
    ServiceDescriptorClient()
    :   thread( ServiceDescriptorClient::run1, this )
    {
    }

    void setEnabled( bool enabled )
    {
        this->enabled = enabled;
    }

    ServiceCache* getServiceCache()
    {
        return &serviceCache;
    }

private:
    void run()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
        while( true ){
            std::unique_lock<std::mutex> lock(mutex);
            semaphore.wait( lock, [this]{ return enabled; } );
            int socketFd = ServiceDescriptorServer::newUdpMulticastSocket( ServiceDescriptorServer::MULTICAST_ADDRESS, ServiceDescriptorServer::PORT );
            uint8_t buffer[100];
            sockaddr_in sockAddrIn;
            socklen_t sizeOfSockAddrIn = sizeof(sockAddrIn);
            while( enabled ){
                ssize_t result = recvfrom( socketFd, buffer, sizeof(buffer), 0, (struct sockaddr*)&sockAddrIn, &sizeOfSockAddrIn );
                std::auto_ptr<avro::InputStream> inputStream = avro::memoryInputStream( buffer, (size_t)result );
                avro::DecoderPtr binaryDecodePtr = avro::binaryDecoder();
                binaryDecodePtr->init(*inputStream);
                ServiceDescriptorSer serviceDescriptorSer;
                avro::decode( *binaryDecodePtr, serviceDescriptorSer );
                serviceCache.addService( new ServiceDescriptor(&serviceDescriptorSer) );
            }
            shutdown( socketFd, 2 );
        }
#pragma clang diagnostic pop
    }

    static void run1( ServiceDescriptorClient* serviceDescriptorClient )
    {
        serviceDescriptorClient->run();
    }
};

#endif //MUON_DISCOVERY_SERVICEDESCRIPTORCLIENT_H