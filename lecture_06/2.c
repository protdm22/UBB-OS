#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int a2b, b2a, n;

    a2b = open("a2b", O_RDONLY);
    b2a = open("b2a", O_WRONLY);

    while(1) {
        if (read(a2b, &n, sizeof(int)) <= 0) {
            break;
        }
        if (n <= 0) {
            break;
        }
        printf("B %d -> %d\n", n, n - 1);
        n--;
        write(b2a, &n, sizeof(int));
    }

    close(a2b);
    close(b2a);
}
