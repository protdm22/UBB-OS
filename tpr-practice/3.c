#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int pid;

void child_handler() {
    printf("Child terminating...\n");
    exit(0);
}

void parent_handler() {
    printf("Parent terminating...\n");
    kill(pid, SIGUSR1);
    wait(0);
}

void zombie_handler() {
    wait(0);
}

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    pid = fork();
    if (pid == 0) { // Child
        signal(SIGUSR1, child_handler);
        while(1) {
            printf("Child working\n");
            sleep(2);
        }
        exit(0);
    } 
    else {
        signal(SIGUSR1, parent_handler);
        signal(SIGCHLD, zombie_handler);
        while(1) {
            printf("Parent working\n");
            sleep(2);
        }
    }
    return 0;
}
