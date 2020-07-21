#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define MAXLINE 256

struct toSend {
    int n1;
    int n2;
};

int main() {

    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    
    if(pid > 0) { // Pai
        
        struct toSend s;

        write(STDOUT_FILENO, "Numbers: ", strlen("Numbers: "));
        scanf("%d %d", &s.n1, &s.n2);
        
        close(fd[READ]);
        write(fd[WRITE], &s, sizeof(s));
        close(fd[WRITE]);

    }
    else if(pid == 0) { // Filho
        close(fd[WRITE]);
        
        int n;
        char toRead[MAXLINE];
        struct toSend r;
    
        n = read(fd[READ], &r, sizeof(r));
        if(n > 0) {
            sprintf(toRead, "Sum: %d\n", r.n1 + r.n2);
            write(STDOUT_FILENO, toRead, strlen(toRead));
            sprintf(toRead, "Diff: %d\n", r.n1 - r.n2);
            write(STDOUT_FILENO, toRead, strlen(toRead));
            sprintf(toRead, "Quocient: %f\n", (double) r.n1 / r.n2); // Does not validate if n2 is 0.
            write(STDOUT_FILENO, toRead, strlen(toRead));
            sprintf(toRead, "Product: %d\n", r.n1 * r.n2);
            write(STDOUT_FILENO, toRead, strlen(toRead));
        }

        close(fd[READ]);
    }
    return 0;
}