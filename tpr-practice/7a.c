#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    if (mkfifo("7fifo1", 0600)>0) {
        printf("Error creating fifo1\n");
        exit(1);
    }
    if (mkfifo("7fifo2", 0600)>0) {
        printf("Error creating fifo2\n");
        exit(1);
    }
    int f_write = open("7fifo2", O_WRONLY);
    int f_read = open("7fifo1", O_RDONLY);

    int guess = 0;
    srandom(time(0));
    while(guess!=10) {
        guess = random() % 10 + 1;
        write(f_write, &guess, sizeof(int));
        printf("A sent: %d\n", guess);
        read(f_read, &guess, sizeof(int));
        printf("A received: %d\n", guess);
    }

    close(f_read);
    close(f_write);

    unlink("7fifo1");
    unlink("7fifo2");
    
    return 0;
}
