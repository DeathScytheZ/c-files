#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdarg.h>


int main(){
    char token[10] = {'3', '5', 'd', 'e', 'w', 'q', 'i', 'o', 'a', 'j'};

    int k = 0;
    for(int i = 0; i < 10; i++){
        if(token[i++] < 100){
            printf("%d done\n", i);
        }
        printf("%d\n", i);
    }
    printf("%d", k);
}
