#include <stdio.h>
#include <signal.h>

void f(int sgn) {
    printf("Nope, buzz off\n");
}

int main() {
    signal(SIGINT, f);
    while(1);
    return 0;
}
