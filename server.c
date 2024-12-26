#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MY_PORT 23
#define MY_IP "127.0.0.1"
#define BACKLOG 10

int main(){
    int sockfd, newfd;
    socklen_t sin_size;
    struct sockaddr_in my_addr;    
    struct sockaddr_in client_addr;    
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = MY_PORT;
    my_addr.sin_addr.s_addr = inet_addr(MY_IP);
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr_in)) == -1){
        perror("bind failed"); 
        exit(1); 
    }
    if(listen(sockfd, BACKLOG) == -1){
        perror("listen failed"); 
        exit(1);
    }
    sin_size = sizeof(struct sockaddr_in);
    newfd = accept(sockfd, (struct sockaddr*)&client_addr, &sin_size);
    if(newfd == -1){
        perror("accept failed");
        exit(1);
    }
    close(sockfd);
}
