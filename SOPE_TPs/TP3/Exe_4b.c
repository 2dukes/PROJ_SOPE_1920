#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>

// processo‐pai escreve "Hello"
// processo‐filho escreve "world!"

int main(void) 
{
    pid_t fatherPid = getpid();
    pid_t pid;
    pid = fork();

    if(pid > 0) // Pai
        write(STDOUT_FILENO, "Hello ", 6);
    else if (pid == 0) // Filho 
    {
        while(getppid() == fatherPid)
        {
            
        }
        write(STDOUT_FILENO, "World !\n", 8);
    }
    
    return 0;
}
