#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(void) {

    int fd[2];
    pipe(fd);

    if(fork() == 0)
    {
        int a = 2;
        close(fd[READ]);
        write(fd[WRITE], &a, sizeof(int));
        exit(0);
    }
    else {
        int a;
        close(fd[WRITE]);
        read(fd[READ], &a, sizeof(int));
        printf("Number Read: %d\n", a);
    }
    
    return 0;
}