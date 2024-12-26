#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_odd;
sem_t sem_even;
int counter = 0;

void* print_even(void* arg){
    while(1){
        sem_wait(&sem_even);
        printf("Even number: %d\n", counter);
        counter++;
        sleep(1);
        sem_post(&sem_odd);
    }
}

void* print_odd(void* arg){
    while(1){
        sem_wait(&sem_odd);
        printf("Odd number: %d\n", counter);
        counter++;
        sleep(1);
        sem_post(&sem_even);
    }
}

int main(){
    pthread_t thread1, thread2;
    sem_init(&sem_even, 0, 1); 
    sem_init(&sem_odd, 0, 0); 
    pthread_create(&thread1, NULL, print_even, NULL);
    pthread_create(&thread2, NULL, print_odd, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&sem_even); 
    sem_destroy(&sem_odd); 
}
