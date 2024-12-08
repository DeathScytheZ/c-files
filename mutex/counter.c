#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
int counter = 0;

void* increment(void* arg){
    int id = *((int*)arg);
    while(counter < 100){
        pthread_mutex_lock(&lock);
        if(counter < 100){
            counter++;
            printf("Thread %d incremented the counter, its new value is: %d\n", id, counter);
            pthread_mutex_unlock(&lock);
        }else{
            pthread_mutex_unlock(&lock);
        }
    }
}

int main(){
    pthread_t thread1, thread2;
    int id1 = 1;
    int id2 = 2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread1, NULL, increment, &id1);
    pthread_create(&thread2, NULL, increment, &id2);
    pthread_join(thread1, NULL); 
    pthread_join(thread2, NULL); 
    pthread_mutex_destroy(&lock);
}
