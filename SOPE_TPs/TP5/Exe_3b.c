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
    pipe(fd);
    pid_t pid = fork();

    if(pid > 0) { // Parent
        close(fd[READ]);

        if(fd[WRITE] != STDOUT_FILENO) { // Redirect STDOUT to Write side of pipe
            if(dup2(fd[WRITE], STDOUT_FILENO) != STDOUT_FILENO) {
                fprintf(stderr, "DUP2 error!\n");
                exit(3);
            }
            close(fd[WRITE]);
        }

        if(execl("/usr/bin/cat", "/usr/bin/cat", argv[1], NULL) < 0) {
            fprintf(stderr, "Exec error!\n");
            exit(3);
        }
    }
    else if(pid == 0) { // Son
        close(fd[WRITE]);
        
        if(fd[READ] != STDIN_FILENO) { // Redirect STDIN to Read side of pipe
            if(dup2(fd[READ], STDIN_FILENO) != STDIN_FILENO) 
            {
                fprintf(stderr, "DUP2 error!\n");
                exit(2);
            }
            close(fd[READ]);
        }

        if(execl("/usr/bin/sort", "/usr/bin/sort", NULL) < 0) {
            fprintf(stderr, "Exec error!\n");
            exit(2);
        }
    }    
}