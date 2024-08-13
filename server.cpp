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

#include <random>

using namespace std;



static const int PORT_SRV = 34567;

random_device rd;   // non-deterministic generator
mt19937 gen(rd());  // to seed mersenne twister.
uniform_int_distribution<> dist(1,255);

class Tserver
{
    //int srv_addr;
    int srv_port;

    int sockfd;

    struct sockaddr_in servaddr;
           socklen_t   servaddr_len;

    struct sockaddr_in cliaddr;
           socklen_t   cliaddr_len;

    unsigned char buf[4];
    int bytes_read;

    bool is_serving = false;

public:
    Tserver(int port): srv_port(port)
    {
        servaddr_len = sizeof(servaddr);
        cliaddr_len  = sizeof(cliaddr);

        memset(&servaddr, 0, servaddr_len); 
        memset(&cliaddr,  0, cliaddr_len );

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

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(srv_port);
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        
        if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            perror("bind");
            return false;
        }

        return true;
    }

    void stop(){
        is_serving = false;
    }

    void start(){
        is_serving = true;
        unsigned char value_x, value_rnd, value_y;
        unsigned int counter=0;
        
        int bytes_read, bytes_write; 
   
        while(is_serving){

            bytes_read = recvfrom(sockfd, (char *)buf, 3, 
                            MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                            &cliaddr_len); 

            if(bytes_read <= 0) break;

            buf[bytes_read] = 0;
            value_x = buf[1];
            value_rnd = dist(gen);
            value_y = value_x % value_rnd;
            buf[1] = value_y;

            bytes_write = sendto(sockfd, (const char *)buf, 3,  
                            MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
                            cliaddr_len);
            
            if(bytes_write <= 0) break;

            cout << counter++ << " - "
                 << "id["  << +buf[0]    << "]" 
                 << ",  '" << +value_x   << "'"
                 << " % '" << +value_rnd << "'"
                 << " = '" << +value_y   << "'" << endl;
        }
        close(sockfd);
    }

};


int main(){


    cout << "Server udp" << endl;
    Tserver ts(PORT_SRV);
    ts.start();

    return 0;
}

