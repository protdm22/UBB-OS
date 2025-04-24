

int c2p[2], p2c[2];

pipe(c2p); // p[0] - read, p[1] - write
pipe(p2c);

int pid=fork();

if (pid == 0) {
    // child process
    int n=10; close(c2p[0]); close(p2c[1]);
    write(c2p[1]. &n, sizeof(int));
    read(p2c[0], &n, sizeof(int));
    close(c2p[1]); close(p2c[0]);
    exit(0);
}

// parent process
int nr; close(c2p[1]); close(p2c[0]);
read(c2p[0], &nr, sizeof(int));
nr+=10;
write(p2c[1], &nr, sizeof(int));
close(c2p[0]); close(p2c[1]);
wait(0);
return 0;
