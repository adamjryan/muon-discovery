/* 
 * File:   ServiceDescriptor.h
 * Author: adam
 *
 * Created on 22 January 2017, 12:58
 */

#ifndef SERVICEDESCRIPTOR_H
#define SERVICEDESCRIPTOR_H

#include <string>
#include <vector>
#include "io/muoncore/discovery/ServiceDescriptorSer.h"
#include "URI.h"
class ServiceDescriptorServer;

class ServiceDescriptor
{
    friend class ServiceDescriptorServer;
    friend class ServiceDescriptorClient;
private:
    ServiceDescriptorSer serviceDescriptorSer;
    std::vector<URI> connectionUris;

public:
    ServiceDescriptor( std::string identifier )
    {
        serviceDescriptorSer.identifier = identifier;
    }
    
    ServiceDescriptor( std::string identifier, std::vector<std::string>* tags, std::vector<std::string>* codecs, std::vector<URI>* connectionUris, std::vector<std::string>* capabilities )
    {
        serviceDescriptorSer.identifier = identifier;
        for( int t = (int)tags->size() - 1; 0 <= t; t-- ){
            serviceDescriptorSer.tags.push_back( tags->at(t) );
        }
        for( int c = (int)codecs->size() - 1; 0 <= c; c-- ){
            serviceDescriptorSer.codecs.push_back( codecs->at(c) );
        }
        for( int c = (int)connectionUris->size() - 1; 0 <= c; c-- ){
            this->/*serviceDescriptorSer.*/connectionUris.push_back( connectionUris->at(c) );
        }
        for( int c = (int)capabilities->size() - 1; 0 <= c; c-- ){
            serviceDescriptorSer.capabilities.push_back( capabilities->at(c) );
        }
    }

    bool equals( ServiceDescriptor* object ){
        if( this == object ){
            return true;
        }
        ServiceDescriptor* serviceDescriptor = dynamic_cast<ServiceDescriptor*>(object);
        if( serviceDescriptor == nullptr ){
            return false;
        }
        return serviceDescriptorSer.identifier.compare( serviceDescriptor->serviceDescriptorSer.identifier ) != 0;
    }

//    size_t hashCode()
    int32_t hashCode()
    {
        return (int32_t)std::hash<std::string>{}(serviceDescriptorSer.identifier);
    }

    std::string getIdentifier()
    {
        return serviceDescriptorSer.identifier;
    }

    std::vector<std::string>* getTags()
    {
        return &serviceDescriptorSer.tags;
    }

    std::vector<std::string>* getCodecs()
    {
        return &serviceDescriptorSer.codecs;
    }

    std::vector<URI>* getConnectionUris()
    {
        return &/*serviceDescriptorSer.*/connectionUris;
    }

    std::vector<std::string>* getCapabilities()
    {
        return &serviceDescriptorSer.capabilities;
    }
private:
    ServiceDescriptor( ServiceDescriptorSer* serviceDescriptorSer )
    :   ServiceDescriptor( serviceDescriptorSer->identifier, &serviceDescriptorSer->tags, &serviceDescriptorSer->codecs, &connectionUris, &serviceDescriptorSer->capabilities )
    {}
};

#endif /* SERVICEDESCRIPTOR_H */