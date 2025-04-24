#include <stdio.h>

int main() {
    int i;

    FILE* f = popen("less","w");
    for(i=99 ; i>0; i--) {
        fprintf(f, "%d bottles of beer on the wall\n", i);
        fprintf(f, "%d bottles of beer\n", i);
        fprintf(f, "%d Yo take on down and pass it around\n", i);
        fprintf(f, "%d bottles of beer on the wall\n", i-1);
    }
    pclose(f);

    return 0;
}
