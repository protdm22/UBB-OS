#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("One argument!\n");
        exit(1);
    }

    mkfifo(argv[1], 0600);
    char filename[100];
    printf("Enter filename: ");
    scanf("%s", filename);
    
    int f_write = open(argv[1], O_WRONLY);

    FILE* fd = fopen(filename, "r");
    int number;

    while(fscanf(fd, "%d", &number)==1) {
        write(f_write, &number, sizeof(int));
    }

    fclose(fd);

    return 0;
}
