#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEST_PORT 23
#define DEST_IP "127.0.0.1"

int main(){
    int sockfd;
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = DEST_PORT;
    //inet_aton(DEST_IP, &dest_addr.sin_addr);
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("socket 1 failed!");
        exit(1);
    }
    if(connect(sockfd, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) == -1){
        perror("connect failed!");     
        close(sockfd);
        exit(1);
    }
    close(sockfd);
}

