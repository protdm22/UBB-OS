#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int id;
    int a;
    int b;
} pthread_arg;

typedef struct {
    int s;
    int p;
} pthread_res;

void *do_stuff(void *arg) {
    pthread_arg *a = (pthread_arg*)arg;
    // printf("%d: a=%d, b=%d\n", a->id, a->a, a->b);
    pthread_res *r;
    r = malloc(sizeof(pthread_res));
    r->s = a->a + a->b;
    r->p = a->a * a->b;
    return (void*)r;
}

int main(int argc, char **argv) {
    int n,i;
    n = atoi(argv[1]);
    pthread_t *t;
    t = malloc(n * sizeof(pthread_t));
    pthread_arg *arg;
    pthread_res **r;
    r = malloc(sizeof(pthread_res*));
    for (i=0;i<n;i++) {
        arg = malloc(sizeof(pthread_arg));
        arg->id = i;
        arg->a = 7-4*i;
        arg->b = 4*i+5;
        pthread_create(&t[i], NULL, do_stuff, (void*)arg);
    }
    for (i=0;i<n;i++)
        pthread_join(t[i], (void**)&r[i]);
    for (i=0;i<n;i++)
        printf("r[%d]: p = %d, s = %d\n", i, r[i]->p, r[i]->s);
}

