#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BEAR_PORTION 10
#define RANGER_SUPPLIES 20
#define HONEY_THRESHOLD 30
#define BEARS 5
#define BEES 100

int honey = 0;

pthread_barrier_t barrier;
sem_t semaphore;
pthread_cond_t conditional;
pthread_mutex_t mutex;

void* bee(void* args) {
    int honey_counter = 0;
    while(1) {
        pthread_mutex_lock(&mutex);
        honey++;
        pthread_mutex_unlock(&mutex);
        honey_counter++;
        if(honey_counter == HONEY_THRESHOLD) {
            pthread_barrier_wait(&barrier);
        }
    }
    return NULL;
}

void* bear(void *args) {
    pthread_barrier_wait(&barrier);
    while(1) {
        sem_wait(&semaphore);
        pthread_mutex_lock(&mutex);
        honey -= BEAR_PORTION;
        if(honey <= 0) {
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_signal(&mutex);
        sem_post(&semaphore);
    }
    return NULL;
}

void* ranger(void *args) {
    while(1) {
        pthread_mutex_lock(&mutex);
        while(honey > 0) 
            pthread_cond_wait(&conditional, &mutex);
        honey += RANGER_SUPPLIES;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {


    return 0;
}
