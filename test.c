#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t lock;

void* counter_incrementer(){
	sleep(rand() % (5 + 1));
	pthread_mutex_lock(&lock);
	counter++;
	printf("counter incremented! \n");
	pthread_mutex_unlock(&lock);
}

int main(){
	pthread_t threads[5];
	pthread_mutex_init(&lock, NULL);
	srand(time(NULL));
	for(int i = 0; i < 5; i++){
		pthread_create(&threads[i], NULL, counter_incrementer, NULL);
	}

	for(int i = 0; i < 5; i++){
		pthread_join(threads[i], NULL);
	}
	
	printf("%d", counter);
}