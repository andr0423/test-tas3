#include "server_udp.h"



using namespace std;

ServerUdp::ServerUdp(int port, in_addr_t host, unsigned char id, const string fname )
    : CommonUdp(port, host, id)
{
    cli_addr_len = sizeof( cli_addr );
    memset( &cli_addr, 0,  cli_addr_len );

    fout.open(fname, std::ios_base::app);
} 

void ServerUdp::start(){
    this->init();

    is_serving = true;

    unsigned char value_x, value_rnd, value_y;
    unsigned int counter=0;
    
    int bytes_read, bytes_write; 

    while(is_serving){

        bytes_read = recvfrom(sockfd, (char *)buf, 3, 
                        MSG_WAITALL, ( struct sockaddr *) &cli_addr,
                        &cli_addr_len); 

        if(bytes_read <= 0) break;
        
        value_x   = buf[1];
        value_rnd = rnd();            
        value_y   = value_x % value_rnd;
        buf[1]    = value_y;

        bytes_write = sendto(sockfd, (const char *)buf, 3,  
                        MSG_CONFIRM, (const struct sockaddr *) &cli_addr, 
                        cli_addr_len);
        
        if(bytes_write <= 0) break;

        // cout
        fout
            << setw(6)
            << counter++ << " - "

            << setw(2) // << setfill('0')
            << "id["  << +buf[0] << "]" 

            << setw(3) << setfill(' ') 
            << ",  '" << +value_x   << "'"
            << " % '" << +value_rnd << "'"
            << " = '" << +value_y   << "'" << endl;

    }

    close(sockfd);
}
