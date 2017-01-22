/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MulticastDiscovery.h
 * Author: adam
 *
 * Created on 22 January 2017, 13:11
 */

#ifndef MULTICASTDISCOVERY_H
#define MULTICASTDISCOVERY_H

#include "Discovery.h"
#include <string>
#include <vector>
using namespace std;

class MulticastDiscovery : public Discovery
{
public:
    static const int PORT = 9898;
    static const char* MULTICAST_ADDRESS;
private:
    vector<ServiceDescriptor*> serviceCache;
    
public:
    MulticastDiscovery()
    {
        
    }
    
    vector<ServiceDescriptor*>* getKnownServices()
    {
        return &serviceCache;
    }

    void advertiseLocalService( ServiceDescriptor* serviceDescriptor )
    {

    }

    void onReady( DiscoveryOnReady* discoveryOnReady )
    {
        discoveryOnReady->call();
    }

    void shutdown()
    {

    }
};

#endif /* MULTICASTDISCOVERY_H */