
#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

#define DEFAULT_PORT 24001
#define MYHOST "221.121.10.10"
using namespace std;

int main(int argc, char *argv[])
{

    //CODE because I'm creating on a window system
    WSADATA WsaDat;
    if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0) {
        cout << "WSA FAILED\n";
        cin.get();
        return 0;
    }
    //CODE because I'm creating on a window system
    //The rest	of	the code	would	suffice alone on Linux

    int sockfd;
    struct sockaddr_in local;
    struct ip_mreq group;
    char databuf[1024];
    int datalen;
    struct sockaddr_in src_addr;    /* Used to receive (addr,port) of sender */

    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))== -1){
        perror("error creating socket \n");
    }
    else{
        printf("socket created \n");
    }
    
    int reuse = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse,
    sizeof(reuse)) == 1){
        perror("error on setsockopt \n");
    }
    else{
        printf("sockopt'd successfully \n");
    }
    
    memset((char *) &local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(DEFAULT_PORT);
    local.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(sockfd, (struct sockaddr*) &local, sizeof(local))== -1){
         perror("error on binding \n");
    }
    else{
         printf("bound \n");
    }
    
    group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
    group.imr_interface.s_addr = inet_addr("224.0.0.1");
    if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
    (char *)&group, sizeof(group))== -1){
         perror("adding group error \n");
         close(sockfd);
         exit(1);
    }
    else{
         printf("adding multicast group \n");
    }
    
    while(1){
      datalen = sizeof(src_addr);
      if((recvfrom(sockfd, databuf, 1024, 0,
         (struct sockaddr *) &src_addr, &datalen))== -1){
            perror("error on recvfrom \n");
         }
        
        
	   printf("Message received: %s \n", databuf);
    
   }
}
