#include <stdio.h>
#include <unistd.h>

int main() {
	printf("before\n");
	if (fork() == 0) {
		sleep(10);
		exit(0);
	}
	return 0;
}
