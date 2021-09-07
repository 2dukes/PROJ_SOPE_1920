#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int global = 1;

int main(void) {
    int local = 2;
    if(fork() > 0) // Parent
    {
        printf("PID = %d; PPID = %d\n", getpid(), getppid());
        global++;
        local--;
    }
    else // Child
    {
        printf("PID = %d; PPID = %d\n", getpid(), getppid());
        global --;
        local++;
    }
    printf("PID = %d - global = %d ; local = %d\n", getpid(), global, local); // Both executed...
    return 0;
}


// There's always the creation of newer processes, but the parent process of the 'parent'
// always remains the same... 11497 (bash). There's independency regarding the variables defined previously.
