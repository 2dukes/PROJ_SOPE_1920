#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid1;
    pid1 = fork();
    int status;

    if(pid1 == 0) // Filho
    {
        pid_t pid2;
        pid2 = fork();
        if(pid2 == 0) // Neto
            write(STDOUT_FILENO, "Hello ", 6);
        else if(pid2 > 0) // Filho
        {
            wait(&status);
            write(STDOUT_FILENO, "my ", 3);
        }    
    }
    else if (pid1 > 0) // Pai
    {
        wait(&status); // Waits for the son
        write(STDOUT_FILENO, "friends!\n", 9);
    }
    
}