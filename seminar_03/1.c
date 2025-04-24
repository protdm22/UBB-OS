#include <unistd.h>
#include <stdio.h>

int main() {
    int i=5;
    //fork(); // duplicates the program with the data until this point
    if (fork() == -1) printf("error\n");            // 2
    if (fork() == 0) printf("child process\n");     // 2*2
    if (fork() > 0) printf("parent process\n");     // 2*2*2
    printf("%d\n", i);
}

