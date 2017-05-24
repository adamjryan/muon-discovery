/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Discovery.h
 * Author: adam
 *
 * Created on 22 January 2017, 13:02
 */

#ifndef DISCOVERY_H
#define DISCOVERY_H

#include <vector>
#include "DiscoveryOnReady.h"
#include "io/muoncore/discovery/ServiceDescriptor.h"
using namespace std;

class Discovery
{
public:
    virtual void setEnabled( bool enabled ) = 0;
    virtual void onReady( DiscoveryOnReady* discoveryOnReady ) = 0;
    virtual void advertiseLocalService( ServiceDescriptor* serviceDescriptor ) = 0;
    virtual void getKnownServices( vector<ServiceDescriptor*>* ) = 0;
};

#endif /* DISCOVERY_H */