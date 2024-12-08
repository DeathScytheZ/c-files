#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(){
    struct sockaddr_in myaddrinin;
    myaddrin.sin_family = AF_INET;
    myaddrin.sin_port = htons(3490);
    inet_aton("127.0.53.9", &myaddrin.sin_addr);
    struct sockaddr 
    printf("Family: %d\n", myaddrin.sin_family); 
    printf("Port: %d\n", myaddrin.sin_port); 
    printf("IP: %s\n", inet_ntoa(myaddrin.sin_addr)); 
}
