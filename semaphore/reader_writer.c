#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


int main(){
    srand(time(NULL));
    pthread_t threads[SIZE];
    int ids[SIZE];
    pthread_mutex_init(&lock, NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    for(int i = 0; i < SIZE; i++){
        ids[i] = i + 1;
        if(i % 2 == 0){
            pthread_create(&threads[i], NULL, produce, &ids[i]);
        }else{
            pthread_create(&threads[i], NULL, consume, &ids[i]);
        }
    }
    for(int i = 0; i < SIZE; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
} 

