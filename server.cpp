#include <netinet/in.h>
#include <iostream>

#include "common/rnd.h"
#include "common/server_udp.h"


using namespace std;

static const int PORT_SRV = 34567;

// class Tserver
// {
//     unsigned char id;
//     in_addr_t srv_host;
//     int srv_port;
//     int sockfd;

//     struct sockaddr_in srv_addr;
//            socklen_t   srv_addr_len;

//     unsigned char buf[4];

//     bool is_serving = false;

//     struct sockaddr_in cli_addr;
//            socklen_t   cli_addr_len;

// public:
//     Tserver(int port, in_addr_t host=INADDR_LOOPBACK, unsigned char id=0 )
//         : srv_host(host), srv_port(port), id(id)
//     {
//         srv_addr_len = sizeof(srv_addr);
//         cli_addr_len  = sizeof(cli_addr);

//         memset(&srv_addr, 0, srv_addr_len); 
//         memset(&cli_addr, 0, cli_addr_len );

//     }

//     bool init()
//     {
//         sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//         if(sockfd < 0)
//         {
//             perror("socket");
//             return false;
//         }

//         srv_addr.sin_family = AF_INET;
//         srv_addr.sin_port = htons(srv_port);
//         srv_addr.sin_addr.s_addr = htonl(srv_host);

//         if(bind(sockfd, (struct sockaddr *)&srv_addr, srv_addr_len) < 0)
//         {
//             perror("bind");
//             return false;
//         }

//         return true;
//     }

//     void stop(){
//         is_serving = false;
//     }

//     void start(){
//         this->init();

//         is_serving = true;

//         unsigned char value_x, value_rnd, value_y;
//         unsigned int counter=0;
        
//         int bytes_read, bytes_write; 
   
//         while(is_serving){

//             bytes_read = recvfrom(sockfd, (char *)buf, 3, 
//                             MSG_WAITALL, ( struct sockaddr *) &cli_addr,
//                             &cli_addr_len); 

//             if(bytes_read <= 0) break;

//             buf[bytes_read] = 0;
//             value_x = buf[1];
//             value_rnd = rnd();            
//             value_y = value_x % value_rnd;
//             buf[1] = value_y;

//             bytes_write = sendto(sockfd, (const char *)buf, 3,  
//                             MSG_CONFIRM, (const struct sockaddr *) &cli_addr, 
//                             cli_addr_len);
            
//             if(bytes_write <= 0) break;

//             cout << setw(6)
//                  << counter++ << " - "
//                  << setw(2) << setfill('0')
//                  << "id["  << +buf[0] << "]" 
//                  << setfill(' ') << setw(3)
//                  << ",  '" << +value_x   << "'"
//                  << " % '" << +value_rnd << "'"
//                  << " = '" << +value_y   << "'" << endl;
//         }

//         close(sockfd);
//     }

// };



int main(){

    cout << "Server udp" << endl;
    ServerUdp ts( PORT_SRV, INADDR_LOOPBACK, rnd() );
    ts.start();

    return 0;
}

