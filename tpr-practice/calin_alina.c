/* Child A takes a random letter and child B employs a strategy to guess it*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int main() {
    int a2b[2],b2a[2];
    pipe(a2b); pipe(b2a);

    int pid1 = fork();
    if (pid1 == 0) { // Child A
        close(a2b[0]); close(b2a[1]);
        srandom(time(0)^getpid());
        char letter = 'A' + (int)(random() % 26);
        char guess;
        int comp=1;
        while(comp!=0) {
            read(b2a[0], &guess, sizeof(char));
            if (guess == letter)
                comp = 0;
            else if (guess < letter)
                comp = -1;
            else
                comp = 1;
            write(a2b[1], &comp, sizeof(int));
        }
        close(b2a[0]); close(a2b[1]);
    } else {
        int pid2 = fork();
        if (pid2 == 0) { // Child B
            close(b2a[0]); close(a2b[1]);
            char left='A', right='Z';
            int comp=1;
            while(comp!=0 && left<=right) {
                char middle = left + (right-left)/2;
                write(b2a[1], &middle, sizeof(char));
                read(a2b[0], &comp, sizeof(int));
                printf("Guess %c\n", middle);
                if(comp==-1)
                    left=middle+1;
                else if(comp==1)
                    right=middle-1;
            }
            close(b2a[1]); close(a2b[0]);
        }}
    wait(0); wait(0);

    return 0;
}
