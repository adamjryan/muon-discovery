
/*
 * File:   main.cpp
 * Author: Adam
 *
 * Created on 16 January 2017, 12:47
 */
#include "Test.h"
#include "ServiceDescriptorServer.h"
using namespace std;

int main( int argc, char** argv )
{
    ServiceDescriptorServer serviceDescriptorServer;
    serviceDescriptorServer.setEnabled(true);
    condition_variable semaphore;
    std::mutex mutex;
    unique_lock<std::mutex> lock(mutex);
    semaphore.wait( lock, []{ return false; } );
    return 0;
}