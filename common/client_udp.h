#pragma once

#include <sys/select.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <random>

#include "rnd.h"
#include "state_mashine.h"



using namespace std;

class ClientUdp
{
    unsigned char id;
    in_addr_t srv_host;
    int srv_port;
    int sockfd;

    struct sockaddr_in srv_addr;
           socklen_t   srv_addr_len;

    unsigned char buf[4];

    bool is_serving = false;
    
    StMashine * stm;

public:
    ClientUdp( int port, in_addr_t host = INADDR_LOOPBACK, unsigned char id=0 );
    bool init();
    void stop();
    void start();
};
