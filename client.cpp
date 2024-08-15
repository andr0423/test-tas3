#include <netinet/in.h>
#include <iostream>

#include "common/rnd.h"
#include "common/client_udp.h"



using namespace std;

static const int PORT_SRV = 34567;

int main(){

    std::cout << "Client udp" << std::endl;

    ClientUdp ts( PORT_SRV, INADDR_LOOPBACK, rnd() );

    ts.start();

    return 0;
}
