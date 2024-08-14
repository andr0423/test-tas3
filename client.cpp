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



using namespace std;

random_device rd;   // non-deterministic generator
mt19937 gen(rd());  // to seed mersenne twister.
uniform_int_distribution<> dist(1,255);

static const int PORT_SRV = 34567;

enum Sn{ A, B , C, D, E, F };

struct state {
    Sn current;
    unsigned char ge;
    Sn ge_step;
    unsigned char lt;
    Sn lt_step;
    Sn another;
};

struct state machine[] = {
    { Sn::A,  10, Sn::B, 5, Sn::C, Sn::A },
    { Sn::B,  50, Sn::C, 5, Sn::D, Sn::B },
    { Sn::C,  90, Sn::D, 5, Sn::E, Sn::C },

    { Sn::D, 130, Sn::D, 5, Sn::F, Sn::E },  // ?

    { Sn::E, 170, Sn::F, 5, Sn::A, Sn::E },

    { Sn::F, 255, Sn::F, 0, Sn::F, Sn::F }   // ?
};


class StMashine {
    state * current_state;

public:
    StMashine() : current_state(&machine[Sn::A]){};
    
    bool step(unsigned char v)
    {
        if ( v >= current_state->ge ) {
            current_state = &machine[current_state->ge_step];
        } else if ( v < current_state->lt ) {
            current_state = &machine[current_state->lt_step];
        } else {
            current_state = &machine[current_state->another];
        }
        return current_state->current < Sn::F;
    };
    
    Sn   getState()
    {
        return current_state->current;
    };
};

class Tclient
{
    int srv_host;
    int srv_port;
    int sockfd;

    struct sockaddr_in srv_addr;
           socklen_t   srv_addr_len;

    unsigned char buf[4];

    bool is_serving;
    
    StMashine * stm;
    //StMashine stm = StMashine();

public:
    Tclient( int port, in_addr_t host = INADDR_LOOPBACK )
        : srv_host(host), srv_port(port)
    {
        srv_addr_len = sizeof(srv_addr);
        memset(&srv_addr, 0, srv_addr_len);

        // this->init();
    };

    ~Tclient(){
        //delete stm;
    };

    bool init(){
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockfd < 0)
        {
            perror("socket");
            return false;
        }

        srv_addr.sin_family = AF_INET;
        srv_addr.sin_port = htons(srv_port);
        srv_addr.sin_addr.s_addr = htonl(srv_host);
        if(connect(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0)
        {
            perror("connect");
            return false;
        }

        return true;
    };
    
    void stop(){
        is_serving = false;
    };

    void start(){
        this->init();

        is_serving = true;
        unsigned int counter=0;
        unsigned char x, y;
        Sn prev, cur;

        stm = new StMashine();
        while(is_serving){

            x = dist(gen);
            buf[0] = 1;  // id
            buf[1] = x;
            buf[2] = 1;  // control bit, server always set 1, no answer 0
            buf[3] = 0;

            send(sockfd, buf, 3, 0);

            memset(&buf,  0, 3);

            recv(sockfd, buf, 3, 0);

            y = buf[1];

            prev = stm->getState();
            is_serving = stm->step(y);
            cur = stm->getState();

            cout << setw(6)
                    << counter++ << " - " 
                    
                    << setw(2) << setfill('0') << dec
                    << "id[" << +buf[0] << "]: "

                    << setw(3) << setfill(' ') << dec
                    << +x << " >> " 

                    << setw(3) << setfill(' ') << dec
                    << +y << " "

                    << "stm(" << (char)(prev+65) << "->" << (char)(cur+65) <<")"
                    << ( is_serving ? "" : " ENDState" )
                    << ( buf[2] == 1 ? "" : " ERR: server no answered" )
                    << endl;

            // if ( counter++ > 300 ){
            //     is_serving = false;
            //     cout << "Limit of 300 requests exceeded..." << endl;
            //     continue;
            // }

            sleep(1);
        }
        close(sockfd);
        delete stm;
    };
};

int main(){

    std::cout << "Client udp" << std::endl;

    Tclient ts(PORT_SRV, INADDR_LOOPBACK);
    ts.start();

    return 0;
}



