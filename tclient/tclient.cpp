#include "tclient.h"



Tclient::Tclient( int port, in_addr_t host)
    : srv_host(host), srv_port(port)
{
        srv_addr_len = sizeof(srv_addr);
        memset(&srv_addr, 0, srv_addr_len);

        //stm = new StMashine();
        cout << "==== init ====" << endl;
        cout << stm.getState() << endl;

        this->init();
}

Tclient::~Tclient(){
        //delete stm;
}

bool Tclient::init()
{
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
}

void Tclient::stop(){
    is_serving = false;
}

void Tclient::start(){
    is_serving = true;

    unsigned int counter=0;
    unsigned char x, y;
    
    //StateMashine * stm = new StateMashine();
    // StMashine * stm = new StMashine();
    Sn prev, cur;

    while(is_serving){

        x = dist(gen);
        buf[0] = 1;  // id
        buf[1] = x;
        buf[2] = 1;  // control bit
        buf[3] = 0;

        send(sockfd, buf, 3, 0);

        memset(&buf,  0, 3);

        recv(sockfd, buf, 3, 0);

        y = buf[1];

        prev = stm.getState();
        is_serving = stm.step(y);
        cur = stm.getState();

        cout << setw(6)
                << counter << " - " 
                << setw(2) << setfill('0')
                << "id[" << +buf[0] << "]: "
                << setfill(' ') << setw(3)
                << +x << " -> " 
            //<< +y << " (" << Sn::A << ") (" << machine[Sn::A].another << ")" 
                << "stm(" << prev <<"->" << cur <<")"
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
    //delete stm;
}

