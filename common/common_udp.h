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

#include "rnd.h"

class CommonUdp
{
protected:

    unsigned char id;
    in_addr_t srv_host;
    int srv_port;
    int sockfd;

    struct sockaddr_in srv_addr;
           socklen_t   srv_addr_len;

    unsigned char buf[128];

    bool is_serving = false;

public:
    CommonUdp(int port, in_addr_t host=INADDR_LOOPBACK, unsigned char id=0 );
    void stop();
    bool init();
    virtual void start() = 0;

};

