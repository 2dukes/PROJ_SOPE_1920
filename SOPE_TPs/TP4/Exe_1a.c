// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo)
{
 printf("In SIGINT handler ...\n");
}

int main(void)
{
    if (signal(SIGINT, sigint_handler) < 0)
    {
        fprintf(stderr,"Unable to install SIGINT handler\n");
        exit(1);
    }
    printf("Sleeping for 30 seconds ...\n");
    unsigned int remainingSeconds = 30; // remainingSeconds will have 0 or the seconds needed to complete the 30 seconds initially instantiated according to the sent signals.
    while(remainingSeconds != 0)
        remainingSeconds = sleep(30);
    
    printf("Waking up ...\n");
    exit(0);
} 

/*

Question A -> 

With SIGINT (CTRL + C), the sleep call leaves after the signal is sent and the handler returns. 
Exit Code is 0 as all was handled properly.

With SIGUSR1, as the handler is the default one, which means it's no treated, the program exits unexpectedly
and the exit code is 138 (128 + 10 (Signal number)).

*/