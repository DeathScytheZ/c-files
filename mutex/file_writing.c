#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 6

pthread_mutex_t lock;

void* write_to_file(void* arg){
    int id = *((int*)arg);
    for(int i = 0; i < 5; i++){
        pthread_mutex_lock(&lock);
        FILE* file = fopen("output.txt", "a"); 
        fprintf(file, "pthread %d was here (:\n", id); 
        fclose(file);
        pthread_mutex_unlock(&lock);
    }
}

int main(){
    pthread_t threads[SIZE];
    int ids[] = {1, 2, 3, 4, 5, 6};
    pthread_mutex_init(&lock, NULL);
    for(int i = 0; i < SIZE; i++){
        pthread_create(&threads[i], NULL, write_to_file, &ids[i]);
    }
    for(int i = 0; i < SIZE; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
}
