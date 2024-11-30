#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t lock;
void* increment(void* arg){
    int id = *((int*)arg);
    while(counter < 100){ 
        sleep(rand() % 3);
	pthread_mutex_lock(&lock);
	counter++;
        printf("Thread %d incremented the counter, new counter value: %d\n", id, counter); 
	pthread_mutex_unlock(&lock);
    }	
    pthread_exit(NULL);
}


int main(){
    pthread_t thread1, thread3;
    int ids[2] = {1, 3};
    srand(time(NULL));
    pthread_mutex_init(&lock,  NULL);
    pthread_create(&thread1, NULL, increment, &ids[0]);
    pthread_create(&thread3, NULL, increment, &ids[1]);
    pthread_join(thread1, NULL);
    pthread_join(thread3, NULL);
    pthread_mutex_destroy(&lock);
}
