#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int a2b[2];
    pipe(a2b);

    if (argc != 2) {
        printf("One argument!\n");
        exit(1);
    }

    int f_read = open(argv[1], O_RDONLY);

    int pid1 = fork();
    if (pid1==0) {
        close(a2b[0]);
        int number;
        int sum=0;
        while(read(f_read, &number, sizeof(int))) {
            sum += number;
        }
        write(a2b[1], &sum, sizeof(int));
        close(a2b[1]);
        close(f_read);
        exit(0);
    }
    else {
        int pid2 = fork();
        if(pid2==0) {
            close(a2b[1]);
            int nr;
            read(a2b[0], &nr, sizeof(int));
            //printf("%d\n", nr);
            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
            for(int i=1;i<=nr;i++)
                if(nr%i==0)
                    printf("%d ", i);
            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

            close(a2b[0]);
            exit(0);
        }
        else {
            wait(0); wait(0);
            
        }}
    
    unlink(argv[1]);

    return 0;
}
