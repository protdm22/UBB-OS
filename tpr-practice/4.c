#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    (void) argc;
    int pid = fork();
    if (pid == -1)
        printf("Error on fork\n");
    else if (pid == 0)
        execvp(argv[1], argv + 1);
    else
        wait(0);
    return 0;
}
