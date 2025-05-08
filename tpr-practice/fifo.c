#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    mkfifo("test_fifo", 0600);
    unlink("test_fifo");
    return 0;
}
