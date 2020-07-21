#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

#define READ 0
#define WRITE 1
#define MAXLINE 256

int main(int argc, char * argv[])
{
    if(argc != 2) {
        printf("Usage: prog filename\n");
        exit(1);
    }

    int fd[2];
    char toRead[MAXLINE];
    pipe(fd);
    pid_t pid = fork();

    if(pid > 0) { // Parent
        close(fd[READ]);
        int fileP = open(argv[1], O_RDONLY);
        int n;
        while((n = read(fileP, toRead, MAXLINE)) != 0) {
            write(fd[WRITE], toRead, n);
        }

        close(fd[WRITE]);
        wait(&n);
        
        exit(0);
    }
    else if(pid == 0) { // Son
        close(fd[WRITE]);
        
        if(fd[READ] != STDIN_FILENO) {
            if(dup2(fd[READ], STDIN_FILENO) != STDIN_FILENO) 
            {
                fprintf(stderr, "DUP2 error!\n");
                exit(2);
            }
            close(fd[READ]);
        }

        if(execl("/usr/bin/sort", "/usr/bin/sort", NULL) < 0) {
            fprintf(stderr, "DUP2 error!\n");
            exit(2);
        }
    }    
}