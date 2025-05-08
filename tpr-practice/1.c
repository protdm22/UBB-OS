#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("There must be only one argument provided!");
        return -1;
    }
    int n = atoi(argv[1]);
    for (int i = 0; i < n; i++) {
        int pid = fork();
        if (pid == -1) {
            perror("Error");
            exit(1);
        } else if (pid == 0) {
            printf("Child %d of parent %d\n", getpid(), getppid());
            exit(0);
        } else {
            printf("Parent %d has child %d\n", getpid(), pid);
        }
    }
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }
}
