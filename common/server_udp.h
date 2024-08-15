#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "common_udp.h"



class ServerUdp : public CommonUdp
{
    struct sockaddr_in cli_addr;
           socklen_t   cli_addr_len;

    ofstream fout;

public:
    ServerUdp(int port, in_addr_t host=INADDR_LOOPBACK, unsigned char id=0, const string fname = "" );
    void start();
    
};
