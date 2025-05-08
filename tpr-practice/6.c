#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[]) {
    int p2c[2], c2p[2];
    pipe(p2c); pipe(c2p);

    int pid = fork();

    if (pid < 0) {
        printf("Fork error\n");
        exit(1);
    } else if (pid == 0) { // Child
        close(p2c[1]); close(c2p[0]);

        int n;
        read(p2c[0], &n, sizeof(int));
        
        int v[n];
        read(p2c[0], &v, sizeof(int) * n);
        
        int sum=0;
        for(int i=0;i<n;i++)
            sum+=v[i];

        double average = (double)sum/(double)n;
        write(c2p[1], &average, sizeof(double));

        close(p2c[0]); close(c2p[1]);
    } else { // Parent
        close(p2c[0]); close(c2p[1]);
        if (argc != 2) {
            printf("There must be only one argument provided\n");
            exit(1);
        }

        int N = atoi(argv[1]);
        int arr[N];
        srand(time(0));

        for(int i=0;i<N;i++) {
            arr[i] = random() % 10000;
        }

        write(p2c[1], &N, sizeof(int));
        write(p2c[1], &arr, sizeof(int) * N);

        double avg;
        read(c2p[0], &avg, sizeof(double));

        printf("%f\n", avg);
        
        wait(0);
        close(p2c[1]); close(c2p[0]);       
    }
    return 0;
}
