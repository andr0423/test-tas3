#include "common_udp.h"



using namespace std;

CommonUdp::CommonUdp(int port, in_addr_t host, unsigned char id )
    : srv_host(host), srv_port(port), id(id)
{
    srv_addr_len = sizeof(srv_addr);
    memset(&srv_addr, 0, srv_addr_len); 

    memset(&buf, 0, 4);

}

bool CommonUdp::init()
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

    auto bnd = bind(sockfd, (struct sockaddr *)&srv_addr, srv_addr_len);
    if( bnd < 0)
    {
        perror("bind");
        return false;
    }

    return true;
}

void CommonUdp::stop(){
    is_serving = false;
}
