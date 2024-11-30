#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){
    int pid = fork();
    if(pid < 0){
        perror("Fork failed");
        return 1;
    }else if(pid == 0){
        printf("This is the child process!, its pid is: %d\n", getpid());
    }else{
        printf("This is the parent process, its pid is: %d\n", getpid());
    }
    printf("Done!\n");
    return 0;
}