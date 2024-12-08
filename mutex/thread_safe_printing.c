#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;

void* print(void* arg){
    int id = *((int*)arg);
    pthread_mutex_lock(&lock);
    printf("\nHey, this is thread %d (:", id);
    pthread_mutex_unlock(&lock);
    sleep(1);
}

int main(){
    pthread_t thread1, thread2, thread3, thread4, thread5;
    pthread_t threads[] = {thread1, thread2, thread3, thread4, thread5};
    int ids[] = {1, 2, 3, 4, 5};
    pthread_mutex_init(&lock, NULL);
    for(int i = 0; i < 5; i++){
        pthread_create(&threads[i], NULL, print, &ids[i]);
    }
    for(int i = 0; i < 5; i++){
        pthread_join(threads[i], NULL); 
    }
    pthread_mutex_destroy(&lock);
}
