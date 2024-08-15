#include "client_udp.h"



ClientUdp::ClientUdp( int port, in_addr_t host, unsigned char id )
         : CommonUdp(port, host, id)
    {}

bool ClientUdp::init()
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
    
    auto bnd = connect(sockfd, (struct sockaddr *)&srv_addr, srv_addr_len);
    if( bnd < 0)
    {
        perror("bind");
        return false;
    }
    return true;
}

void ClientUdp::start(){

    this->init();
    
    is_serving = true;
    unsigned char x, y;
    unsigned int counter=0;
    Sn prev, cur;

    stm = new StMashine();

    while(is_serving){

        x = rnd();

        buf[0] = id;  // id
        buf[1] = x;
        buf[2] = 1;   // control bit, server always set 1, no answer 0
        buf[3] = 0;

        send(sockfd, buf, 3, 0);

        memset(&buf,  0, 3);

        recv(sockfd, buf, 3, 0);

        y = buf[1];

        prev = stm->getState();
        is_serving = stm->step(y);
        cur = stm->getState();


        cout 
            << setw(6)
            << counter << " - " 
            
            << "id[" << setw(2) << setfill(' ') << dec << +buf[0] << "]: "

            << setw(3) << setfill(' ') << dec
            << +x << " >> " 

            << setw(3) << setfill(' ') << dec
            << +y << " "

            << "stm(" << (char)(prev+65) << "->" << (char)(cur+65) <<")"
            << ( is_serving  ? "" : " ENDState" )
            << ( buf[2] == 1 ? "" : " ERR: server is not answered" )
            << endl;

        if ( counter > 500 ){
            is_serving = false;
            cout << "Limit of 500 requests exceeded..." << endl;
            continue;
        }
        counter++;

        //sleep(1);
        this_thread::sleep_for(std::chrono::milliseconds(rnd()));

    }
    close(sockfd);
    delete stm;
}

