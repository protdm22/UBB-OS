#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int a[4] = {1,2,3,4};

    int p[2]; // p[0] for read, p[1] for write

    pipe(p);
    if(fork() == 0) {
        close(p[0]);
        a[2] += a[3];
        write(p[1], &a[2], sizeof(int));
        close(p[1]);
        exit(0);
    }
    close(p[1]);
    a[0] += a[1];
    read(p[0], &a[2], sizeof(int));
    close(p[0]);
    wait(0);

    a[0] += a[2];
    printf("%d\n", a[0]);
    return 0;
}
