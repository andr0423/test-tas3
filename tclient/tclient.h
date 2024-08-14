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

// # i n c lude "../rnd.h"
#include "state_mashine.h"

#include <random>

using namespace std;

random_device rd;   // non-deterministic generator
mt19937 gen(rd());  // to seed mersenne twister.
uniform_int_distribution<> dist(1,255);

using namespace std;

class Tclient
{
    int srv_host;
    int srv_port;
    int sockfd;

    struct sockaddr_in srv_addr;
           socklen_t   srv_addr_len;

    unsigned char buf[4];

    bool is_serving;
    
    //StMashine * stm;
    StMashine stm = StMashine();

public:
    Tclient( int port, in_addr_t host = INADDR_LOOPBACK );
    ~Tclient();
    bool init();
    void stop();
    void start();
};
