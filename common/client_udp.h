#pragma once

#include <chrono>
#include <thread>
#include "state_mashine.h"
#include "common_udp.h"

using namespace std;

class ClientUdp : public CommonUdp
{
    StMashine * stm;

public:
    ClientUdp( int port, in_addr_t host = INADDR_LOOPBACK, unsigned char id=0 );
    bool init();
    void start();
};
