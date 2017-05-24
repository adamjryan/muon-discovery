/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test.h
 * Author: adam
 *
 * Created on 22 January 2017, 13:00
 */

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <cstdlib>
//#include <stdlib.h>
//#include <stddef.h>
#include <netdb.h>
#include <string>
using namespace std;

void init_sockaddr( struct sockaddr_in *name, const char *hostname, uint16_t port )
{
    struct hostent* hostinfo;
    name->sin_family = AF_INET;
    name->sin_port = htons(port);
    hostinfo = gethostbyname(hostname);
    if (hostinfo == NULL) {
        fprintf(stderr, "Unknown host %s.\n", hostname);
        exit(EXIT_FAILURE);
    }
    name->sin_addr = *(struct in_addr *) hostinfo->h_addr;
}

void handleNewConnections( string msg )
{
}

#endif /* TEST_H */