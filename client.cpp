#include<sys/select.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

#include <random>

using namespace std;



static const int PORT_SRV = 34567;

random_device rd;   // non-deterministic generator
mt19937 gen(rd());  // to seed mersenne twister.
uniform_int_distribution<> dist(1,255);

class Tclient
{
    int srv_host;
    int srv_port;
    int sockfd;

    struct sockaddr_in srv_addr;
    socklen_t          srv_addr_len;

    unsigned char buf[4];

    bool is_serving;

public:
    Tclient(in_addr_t host, int port): srv_host(host), srv_port(port)
    {
        this->init();
    }

    bool init()
    {
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockfd < 0)
        {
            perror("socket");
            return false;
        }


        srv_addr.sin_family = AF_INET;
        srv_addr.sin_port = htons(PORT_SRV);
        srv_addr.sin_addr.s_addr = htonl(srv_host);
        if(connect(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0)
        {
            perror("connect");
            return false;
        }

        return true;
    }

    void stop(){
        is_serving = false;
    }

    void start(){
        is_serving = true;

        unsigned int counter=0;
        unsigned char x, y;
        while(is_serving){

            x = dist(gen);
            buf[0] = 1;  // id
            buf[1] = x;
            buf[2] = 1;  // control bit
            buf[3] = 0;

            send(sockfd, buf, 3, 0);

            // buf[0] = buf[1] = buf[2] = 0;
            memset(&buf,  0, 3);

            recv(sockfd, buf, 3, 0); 

            y = buf[1];
            cout << counter << " - " << +buf[0] << ": "
                 << +x << " -> " 
                 << +y << " " 
                 << ( buf[2] == 1 ? "" : "FAIL" ) << endl;

            if ( counter++ > 9 ){
                is_serving = false;
                continue;
            }

            sleep(1);
        }

        close(sockfd);
    }

};


int main(){

    cout << "Client udp" << endl;

    Tclient ts(INADDR_LOOPBACK, PORT_SRV);
    ts.start();

    return 0;
}



