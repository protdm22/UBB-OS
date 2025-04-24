#include <unistd.h>
#include <stdio.h>

int main() {
    int i=5;
    int p = fork();     // 2: P, C
    if (p == -1) printf("error\n");
    if (p == 0) {
        i=10;
        printf("child process\n");
        // child code
        exit(45);
    }
    i=20;
    printf("parent process\n");

    // parent code
    int status;

    wait(p, &status); 

    printf("%d\n", i);
    return 0;
}


