#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t m;
int n = 0;

void *do_stuff(void *arg) {
    int i;
    for (i=0;i<1000;i++) {
        pthread_mutex_lock(&m);
        n++;
        pthread_mutex_unlock(&m);
    }

    return 0;
}

int main(int argc, char **argv) {
    int i;
    pthread_mutex_init(&m, NULL);
    pthread_t t[1000];
    for (i=0;i<1000;i++) {
        pthread_create(&t[i], NULL, do_stuff, NULL);
    }
    for (i=0;i<1000;i++)
        pthread_join(t[i], NULL);
    pthread_mutex_destroy(&m);
    printf("n=%d\n", n);
    return 0;
}

