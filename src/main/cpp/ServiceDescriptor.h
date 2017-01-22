/* 
 * File:   ServiceDescriptor.h
 * Author: adam
 *
 * Created on 22 January 2017, 12:58
 */

#ifndef SERVICEDESCRIPTOR_H
#define SERVICEDESCRIPTOR_H

#include "URI.h"
#include <string>
#include <vector>
using namespace std;

class ServiceDescriptor
{
public:
    const string identifier;
    vector<string> tags;
    vector<string> codecs;
    vector<URI> connectionUrls;
    vector<string> capabilities;

public:
    ServiceDescriptor( string identifier )
    :   identifier(identifier)
    {
    }
    
    ServiceDescriptor( string identifier, vector<string>* tags, vector<string>* codecs, vector<URI>* connectionUrls, vector<string>* capabilities )
    :   identifier(identifier)
    {
        for( int t = tags->size(); 0 <= t; t-- ){
            this->tags.push_back( tags->at(t) );
        }
        for( int c = codecs->size(); 0 <= c; c-- ){
            this->codecs.push_back( codecs->at(c) );
        }
        for( int c = connectionUrls->size(); 0 <= c; c-- ){
            this->connectionUrls.push_back( connectionUrls->at(c) );
        }
        for( int c = capabilities->size(); 0 <= c; c-- ){
            this->capabilities.push_back( capabilities->at(c) );
        }
    }

    bool equals( ServiceDescriptor* o ){
        if( this == o ){
            return true;
        }
        o = dynamic_cast<ServiceDescriptor*>(o);
        if( o == NULL ){
            return false;
        }
        return identifier.compare( o->identifier ) != 0;
    }

    size_t hashCode()
    {
        return hash<string>{}(identifier);
    }

    string* getCodecs()
    {
        return &codecs[0];
    }
    
    vector<string>* getTags() {
        return &tags;
    }

    string getIdentifier()
    {
        return identifier;
    }

    vector<URI>* getConnectionUrls()
    {
        return &connectionUrls;
    }

    vector<string>* getCapabilities()
    {
        return &capabilities;
    }
};

#endif /* SERVICEDESCRIPTOR_H */