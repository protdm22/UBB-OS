#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_barrier_t bar;
pthread_mutex_t m;
pthread_cond_t c, c2;
int n;
int mww = 0;

void *worker(void *arg) {
    int i;
    pthread_barrier_wait(&bar);
    for(i=0;i<(int)arg;i++) {
        pthread_mutex_lock(&m);
        if (mww > 0)
            pthread_cond_wait(&c2, &m);
        n++;
        if (n % 200 == 0) {
            //printf("Sending signal\n");
            if (mww!=-1)
                mww = 1;
            pthread_cond_signal(&c);
        }
        pthread_mutex_unlock(&m);
    }
    return 0;
}

void *waiter(void *arg) {
    pthread_mutex_lock(&m);
    pthread_barrier_wait(&bar);
    //printf("Waiting for signal\n");
    pthread_cond_wait(&c, &m);
    printf("n = %d\n", n);
    pthread_mutex_unlock(&m);
    mww = -1;
    pthread_cond_broadcast(&c2);
    return 0;
}

int main(int argc, char *argv[]) {
    int i,a,b;
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    
    pthread_t *t, w;
    t = malloc(a * sizeof(pthread_t));
    pthread_barrier_init(&bar, NULL, a+1);
    pthread_cond_init(&c, NULL);
    pthread_cond_init(&c2, NULL);

    for (i=0;i<a;i++) {
        pthread_create(&t[i], NULL, worker, (void *)b);
    }
    
    pthread_create(&w, NULL, waiter, NULL);
    
    for (i=0;i<a;i++) {
        pthread_join(t[i], NULL);
    }

    pthread_join(w, NULL);
    free(t);
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);
    
    return 0;
}
