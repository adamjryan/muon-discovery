/* 
 * File:   main.cpp
 * Author: Adam
 *
 * Created on 16 January 2017, 12:47
 */
#include "ServiceDescriptorServer.h"
using namespace std;

int main2( int argc, char** argv )
{
    ServiceDescriptorServer serviceDescriptorServer;
//    serviceDescriptorServer.setEnabled(true);
    serviceDescriptorServer.getServices(true);
    return 0;
}