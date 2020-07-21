#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

void full_copy(int from, int to) {
    char buffer[50];
    size_t n;
    while((n = read(from, buffer, 50)) > 0)
        write(to, buffer, n);


    close(from);
    close(to);
}

int main(int argc, char* argv[]) {
    int fd[2];
    int desc;

    if(argc != 2)
        exit(1);
    if((desc = open(argv[1], O_RDONLY)) == -1)
        exit(1);
    if(pipe(fd) == -1)
        exit(1);
    
    pid_t pid = fork();
    if(pid < 0)
        exit(1);
    
    if(pid == 0) {
        dup2(fd[READ], STDIN_FILENO);
        close(fd[WRITE]);
        execlp("cat", "cat", NULL);
        exit(1);
    }
    
    close(fd[READ]);
    full_copy(desc, fd[WRITE]);
    wait(NULL);
    return 0;
}