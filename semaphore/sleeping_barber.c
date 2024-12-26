#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define num_costumers 10 

int waiting_room = 4;
sem_t sleeping;
pthread_mutex_t lock;

void* func(void* arg){
    return NULL;
}

void* func2(void* arg){
    return NULL;
}

int main(){
    pthread_t barber;
    pthread_t costumers[num_costumers];
    int ids[num_costumers];
    sem_init(&sleeping, 0, 1);
    pthread_mutex_init(&lock, 0);
    pthread_create(&barber, NULL, func, NULL); 
    for(int i = 0; i < num_costumers; i++){
        ids[i] = i + 1;
        pthread_create(&costumers[i], NULL, func2, &ids[i]);
    }
    pthread_join(barber, NULL);
    for(int i = 0; i < num_costumers; i++){
        pthread_join(costumers[i], NULL); 
    }
    sem_destroy(&sleeping);
    pthread_mutex_destroy(&lock);
}

