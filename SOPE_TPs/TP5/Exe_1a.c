#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define MAXLINE 256

int main() { // Like topic c)

    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    
    // Could have passed an array of integers as in Exe_1.c which was what it was actually asked in topic a) :3

    if(pid > 0) { // Pai
        

        int n1, n2;
        char toWrite[MAXLINE];
        write(STDOUT_FILENO, "Numbers: ", strlen("Numbers: "));
        scanf("%d %d", &n1, &n2);
        
        sprintf(toWrite, "%d %d", n1, n2);
        
        close(fd[READ]);
        write(fd[WRITE], toWrite, strlen(toWrite));
        close(fd[WRITE]);

    }
    else if(pid == 0) { // Filho
        close(fd[WRITE]);
        
        char toRead[MAXLINE];
        int n1, n2, n;

        n = read(fd[READ], toRead, MAXLINE);
        if(n > 0) {
            sscanf(toRead, "%d %d", &n1, &n2);
            sprintf(toRead, "Sum: %d\n", n1 + n2);
            write(STDOUT_FILENO, toRead, strlen(toRead));
            sprintf(toRead, "Diff: %d\n", n1 - n2);
            write(STDOUT_FILENO, toRead, strlen(toRead));
            sprintf(toRead, "Quocient: %f\n", (double) n1 / n2); // Does not validate if n2 is 0.
            write(STDOUT_FILENO, toRead, strlen(toRead));
            sprintf(toRead, "Product: %d\n", n1 * n2);
            write(STDOUT_FILENO, toRead, strlen(toRead));
        }

        close(fd[READ]);
    }
    return 0;
}