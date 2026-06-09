#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty; // counts empty slots
sem_t full; // counts filled slots
pthread_mutex_t mutex; // for mutual exclusion
void* producer(void* arg){
    int item, i = 0;
    while (1){
        item = i++; // produce an item (here just incrementing number)
        sem_wait(&empty); // wait for empty slot
        pthread_mutex_lock(&mutex); // enter critical section
        buffer[in] = item;
        printf("Produced: %d at buffer[%d]\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex); // leave critical section
        sem_post(&full); // signal that new item is available
        sleep(1); // simulate time to produce
    }
}

void* consumer(void* arg){
    int item;
    while (1){
        sem_wait(&full); // wait for filled slot
        pthread_mutex_lock(&mutex); // enter critical section
        item = buffer[out];
        printf("Consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex); // leave critical section
        sem_post(&empty); // signal that a slot is free
        sleep(2); // simulate time to consume
    }
}

void main(){
    pthread_t prod, cons;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
}