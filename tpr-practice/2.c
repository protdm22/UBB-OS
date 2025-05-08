#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("There must be one parameter");
        exit(1);
    }
    int n = atoi(argv[1]);
    for (int i=0;i<n;i++) {
        int pid = fork();
        if (pid == -1) {
            perror("");
            exit(1);
        } else if (pid == 0) {
            printf("child %d of parent %d\n", getpid(), getppid());
        } else {
            printf("parent %d has child %d\n", getpid(), pid);
            wait(NULL);
            exit(0);
        }
    }
}
