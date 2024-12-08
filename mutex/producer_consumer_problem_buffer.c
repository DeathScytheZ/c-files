#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
int item[5];
int available_slot = 0;
int c = 20;

void* produce(void* arg){
    int id = *((int*)arg);
    while(c > 0){
        pthread_mutex_lock(&lock);
        if(c > 0 && available_slot < 5){
            item[available_slot] = rand() % 100 + 1; 
            printf("Item (%d) has been produced by thread %d:\n", item[available_slot], id);
            available_slot ++;
            c--;
        }
        pthread_mutex_unlock(&lock);
    }
}

void* consume(void* arg){
    int id = *((int*)arg);
    while(c > 0){
        pthread_mutex_lock(&lock);
        if(c > 0 && available_slot > 0){
            int temp = item[available_slot - 1];
            available_slot --;
            item[available_slot] = 0; 
            printf("Item (%d) has been consumed by thread %d:\n", temp, id);
            c--;
        }
        pthread_mutex_unlock(&lock);
    }
}

int main(){
    srand(time(NULL));
    pthread_t thread1, thread2, thread3, thread4, thread5, thread6;
    pthread_t threads[] = {thread1, thread2, thread3, thread4, thread5, thread6}; 
    int ids[] = {1, 2, 3, 4, 5, 6};
    pthread_mutex_init(&lock, NULL);
    for(int i = 0; i < 6; i++){
        if(i % 2 == 0){
            pthread_create(&threads[i], NULL, produce, &ids[i]);
        }else{
            pthread_create(&threads[i], NULL, consume, &ids[i]);
        }
    }
    for(int i = 0; i < 6; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    printf("[");
    for(int i = 0; i < 4; i++){
        printf("%d, ", item[i]);
    }
    printf("%d", item[4]);
    printf("]");
}




