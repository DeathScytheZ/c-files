#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 4
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3

sem_t empty, full;
pthread_mutex_t lock;
pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
int ids[NUM_PRODUCERS + NUM_CONSUMERS] = {1, 2, 3, 4, 5, 6};
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

void* produce_item(void* arg) {
    int id = *((int*)arg);
    while (1) {
        int item = rand() % 100; // Generate a random item
        sem_wait(&empty); // Wait for an empty slot
        pthread_mutex_lock(&lock);

        // Critical section
        buffer[in] = item;
        printf("Producer %d produced item %d at position %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&lock);
        sem_post(&full); // Signal a full slot
        sleep(rand() % 3); // Simulate time to produce
    }
}

void* consume_item(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&full); // Wait for a full slot
        pthread_mutex_lock(&lock);

        // Critical section
        int item = buffer[out];
        printf("Consumer %d consumed item %d from position %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&lock);
        sem_post(&empty); // Signal an empty slot
        sleep(rand() % 3); // Simulate time to consume
    }
}

int main() {
    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&lock, NULL);
    srand(time(NULL));

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, produce_item, &ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consume_item, &ids[NUM_PRODUCERS + i]);
    }

    // Join threads (this will block forever since threads run infinite loops)
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores and mutex (unreachable in this example)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);

    return 0;
}
