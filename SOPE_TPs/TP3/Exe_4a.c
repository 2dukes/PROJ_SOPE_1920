#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>

// processo‐filho escreve "Hello"
// processo‐pai escreve "world!"

int main(void) 
{
    pid_t pid;
    int status;
    pid = fork();

    if(pid == 0) // Filho
        write(STDOUT_FILENO, "Hello ", 6);
    else if (pid > 0) // Pai
    {
        wait(&status);
        write(STDOUT_FILENO, "World !\n", 8);
    }
    
    return 0;
}
