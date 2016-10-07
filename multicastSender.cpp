
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
    int sockfd;
    struct in_addr local;
    struct sockaddr_in group;

    char line[] = "Welcome to my group";
    
    //CODE because I'm creating on a window system
    WSADATA WsaDat;
    if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0) {
        cout << "WSA FAILED\n";
        cin.get();
        return 0;
    }
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))==-1){
        perror("error on sockfd \n");
    }
    else{
        printf("send socket created \n");
    }
    
    memset((char *) &group, 0, sizeof(group));
    group.sin_family = AF_INET;
    group.sin_addr.s_addr = inet_addr("226.1.1.1");
    group.sin_port = htons(DEFAULT_PORT);
    
    local.s_addr = inet_addr("224.0.0.1");
    if(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char *)
    &local, sizeof(local)) == -1){
         perror("setting local interface error \n");
         exit(1);
    }
    else {
         printf("local interface set");
    }
          
  
    while(1){
        if((sendto(sockfd, line, strlen(line)+1, 0,(struct 
        sockaddr*)&group, sizeof(group))) == -1){
            perror("error on send \n");
        }
        else{
            printf("sending: %s \n", line);
        }
     }
     
     return 0;
 }
   
