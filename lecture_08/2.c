#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int turn = 0;
int board[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
pthread_mutex_t m0, m1;
sem_t s0, s1;

void show() {
    int i, j;
    printf("Next: %d\n", turn);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%3d", board[i][j]);
        }
        printf("\n");
    }
}

void *p0(void *a) {
    int i, j, full;
    while(1) {
        sem_wait(&s0);
        full = 1;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == -1) {
                    full = 0;
                    board[i][j] = 0;
                    goto DONE;
                }
            }
        }
DONE:
        turn = 1;
        show();
        if (full) {
            sem_post(&s1);
            break;
        }
        sem_post(&s1);
    }
    (void) a;
    return NULL;
}
void *p1(void *a) {
    int i, j, full;
    while(1) {
        sem_wait(&s1);
        full = 1;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == -1) {
                    full = 0;
                    board[i][j] = 1;
                    break;
                }
            }
            if (!full) {
                break;
            }
        }
        turn = 0;
        show();
        if (full) {
            sem_post(&s0);
            break;
        }
        sem_post(&s0);
    }
    (void) a;
    return NULL;
} 

int main() {
    pthread_t t0, t1;

    sem_init(&s0, 0, 1);
    sem_init(&s1, 0, 1);
    sem_wait(&s1);

    pthread_mutex_init(&m0, NULL);
    pthread_mutex_init(&m1, NULL);
    pthread_mutex_lock(&m1);

    pthread_create(&t0, NULL, p0, NULL);
    pthread_create(&t1, NULL, p1, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    sem_destroy(&s0);
    sem_destroy(&s1);

    return 0;
}

