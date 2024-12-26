#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define num_threads 4
int result = 0;
int current = 0;
sem_t semaphore;
int n;

void* sum(void* arg){
    int id = *((int*)arg);
    while(current < n){
        sem_wait(&semaphore);
        if(current < n){
            current++;
            result += current;
            printf("Thread %d incremented the value of result, the new value is: %d\n", id, result);
            usleep(500000);
        }
        sem_post(&semaphore);
        usleep(50000);
    }
    pthread_exit(NULL);
}

int main(){
    int result_seq = 0;
    printf("Enter a number: ");
    scanf("%d", &n);
    pthread_t threads[num_threads];;
    int ids[num_threads];
    sem_init(&semaphore, 0, 1);
    for(int i = 0; i < num_threads; i++){
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, sum, &ids[i]);
    }
    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaphore); 
    printf("Calculating the sum via threads: \n");
    printf("The sum from 1 to %d is: %d\n", n, result);
    for(int i = 1; i <= n; i++){
        result_seq += i;
    }
    printf("Calculating the sum sequantialy: \n");
    printf("The sum from 1 to %d is: %d\n", n, result_seq);
}
