#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
int item;
int item_available = 0;


void* produce(void* arg){
    while(1){
        pthread_mutex_lock(&lock);
        if(!item_available){
            item = rand() % 100 + 1; 
            item_available = 1;
            printf("an Item has been produced: %d\n", item);
        }
        pthread_mutex_unlock(&lock);
    }
}

void* consume(void* arg){
    while(1){
        pthread_mutex_lock(&lock);
        if(item_available){
            item = 0; 
            item_available = 0;
            printf("The item has been consumed: 0\n");
        }
        pthread_mutex_unlock(&lock);
    }
}

int main(){
    srand(time(NULL));
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread1, NULL, produce, NULL);
    pthread_create(&thread2, NULL, consume, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&lock);
    

}
