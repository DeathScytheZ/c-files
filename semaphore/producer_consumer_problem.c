#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define SIZE 6 
pthread_mutex_t lock;
sem_t semEmpty;
sem_t semFull;
int items[10];
int next_slot = 0;

void* produce(void* arg){
    int id = *((int*)arg);
    sem_wait(&semEmpty); 
    pthread_mutex_lock(&lock);
    items[next_slot] = rand() % 101 + 1; 
    next_slot++;
    printf("An item has been produced.\n");
    pthread_mutex_unlock(&lock);
    sem_post(&semFull);
    return NULL;
}

void* consume(void* arg){
    int id = *((int*)arg);
    sem_wait(&semFull); 
    pthread_mutex_lock(&lock);
    int consumed_item = items[next_slot - 1];
    next_slot--;
    printf("Item %d has been consumed.\n", consumed_item);
    pthread_mutex_unlock(&lock);
    sem_post(&semEmpty);
    return NULL;
}

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
