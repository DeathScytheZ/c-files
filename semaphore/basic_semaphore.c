#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

sem_t semaphore;

void* print(void* arg){
    int id = *((int*)arg);
    sem_wait(&semaphore);
    printf("Hey, this is thread %d (:\n", id);
    sem_post(&semaphore);
    return NULL;
}

int main(){
    pthread_t threads[SIZE];
    int ids[SIZE];
    sem_init(&semaphore, 0, 1); 
    for(int i = 0; i < SIZE; i++){
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, print, &ids[i]);
    }
    for(int i = 0; i < SIZE; i++){
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaphore);
}
