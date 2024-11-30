#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int shared = 50;
sem_t semaphore;

void* something(void* arg){
    int id = *((int*)arg);
    while(shared < 100 && shared > 0){
	sem_wait(&semaphore);
	sleep(rand() % 2);
	int opp = rand() % 2;
	if(opp == 0){
	    shared++;
            printf("Thread %d has incremented the shared counter, its new value is: %d\n", id, shared);
	}else{
            shared--;
            printf("Thread %d has decremented the shared counter, its new value is: %d\n", id, shared);
	}
	sem_post(&semaphore);
    }
}

int main(){
    sem_init(&semaphore, 0, 3);
    pthread_t threads[6];
    int ids[6] = {1, 2, 3, 4, 5, 6};
    for(int i = 0; i < 6; i++){
	pthread_create(&threads[i], NULL, something, &ids[i]);
    }
    for(int i = 0; i < 6; i++){
	pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaphore);


}
