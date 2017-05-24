
/*
 * File:   main.cpp
 * Author: Adam
 *
 * Created on 16 January 2017, 12:47
 */
#include "io/muoncore/discovery/MulticastDiscovery.h"

int main( int argc, char** argv )
{
    ServiceDescriptor serviceDescriptor("debug-service");
    serviceDescriptor.getTags()->push_back("tag-0");
    serviceDescriptor.getCapabilities()->push_back("capability-0");
    serviceDescriptor.getCodecs()->push_back("codec-0");

    MulticastDiscovery multicastDiscovery;
    multicastDiscovery.advertiseLocalService(&serviceDescriptor);

    condition_variable semaphore;
    std::mutex mutex;
    unique_lock<std::mutex> lock(mutex);
    semaphore.wait( lock, []{ return false; } );
    return 0;
}