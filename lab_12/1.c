#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_barrier_t bar;

void *do_stuff(void *arg) {
    printf("Thread %d started.\n", (int)arg);
    printf("Thread %d waiting for the barrier...\n", (int)arg);
    pthread_barrier_wait(&bar);
    printf("Thread %d passed the barrier.\n", (int)arg);
    return 0;
}

int main(int argc, char *argv[]) {
    int i,n,m;
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    pthread_t *t;
    t = malloc(sizeof(pthread_t) * n);
    pthread_barrier_init(&bar, NULL, m);
    for (i=0;i<n;i++) {
        pthread_create(&t[i], NULL, do_stuff, (void *)i);
    }
    for (i=0;i<n;i++) {
        pthread_join(t[i], NULL);
    }
    pthread_barrier_destroy(&bar);
    return 0;
}
