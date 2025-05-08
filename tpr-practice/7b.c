#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    int f_read = open("7fifo2", O_RDONLY);
    int f_write = open("7fifo1", O_WRONLY);

    srandom(getpid());

    int guess = 0;
    while(guess!=10) {
        read(f_read, &guess, sizeof(int));
        printf("B received: %d\n", guess);
        guess = random() % 10 + 1;
        write(f_write, &guess, sizeof(int));
        printf("B sent: %d\n", guess);
    }
    

    close(f_read);
    close(f_write);
    return 0;
}
