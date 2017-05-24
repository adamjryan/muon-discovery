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
#include "ServiceDescriptorServer.h"
#include "ServiceDescriptorClient.h"
#include <string>
#include <vector>

class MulticastDiscovery : public Discovery
{
private:
    ServiceDescriptorServer serviceDescriptorServer;
    ServiceDescriptorClient serviceDescriptorClient;

public:
    MulticastDiscovery()
    {
        serviceDescriptorServer.setEnabled(true);
        serviceDescriptorClient.setEnabled(true);
    }

    void setEnabled( bool enabled )
    {
        serviceDescriptorServer.setEnabled(enabled);
        serviceDescriptorClient.setEnabled(enabled);
    }

    void onReady( DiscoveryOnReady* discoveryOnReady )
    {
        discoveryOnReady->call();
    }

    void advertiseLocalService( ServiceDescriptor* serviceDescriptor )
    {
        serviceDescriptorServer.setServiceDescriptor(serviceDescriptor);
    }
    
    void getKnownServices( vector<ServiceDescriptor*>* serviceDescriptors )
    {
        serviceDescriptorClient.getServiceCache()->getServices(serviceDescriptors);
    }
};

#endif /* MULTICASTDISCOVERY_H */