#include <netinet/in.h>
#include <iostream>

#include "common/rnd.h"
#include "common/server_udp.h"


using namespace std;

static const int PORT_SRV = 34567;

int main(){

    cout << "Server udp" << endl;
    ServerUdp ts( PORT_SRV, INADDR_LOOPBACK, rnd() , "server.log");
    ts.start();

    return 0;
}

