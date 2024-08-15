#include <netinet/in.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "common/client_udp.h"
#include "common/server_udp.h"



using namespace std;

int main(){

    const int PORT_SRV = 34567;

    cout << "==== ==== test-task3 is running = ==== ==== ====" << endl;

    ServerUdp * srv = new ServerUdp( PORT_SRV, INADDR_LOOPBACK, 0, "main.log" );
    thread th_server( &ServerUdp::start, srv);
    th_server.detach();

    ClientUdp * clnt[32];
    thread * thrds[32];
    for (int i; i < 32 ; i++){
        clnt[i] = new ClientUdp( PORT_SRV, INADDR_LOOPBACK, (unsigned char) i );
        thrds[i] = new thread ( &ClientUdp::start, clnt[i] );
    }

    for ( auto th : thrds ){
        th->join();
    }

    cout << "==== ==== all threads are over == ==== ==== ====" << endl;
    sleep(3);
    srv->stop();

    delete srv;

    for ( int i; i < 32 ; i++){
        delete clnt[i];
        delete thrds[i];
    }

    cout << "==== ==== test-task3 is completed ==== ==== ====" << endl;
    
    return 0;
}
