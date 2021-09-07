#define _POSIX_SOURCE

// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <features.h>


void sigint_handler(int signo)
{
 printf("In SIGINT handler ...\n");
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = sigint_handler;

    sigemptyset(&act.sa_mask);
    // sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = 0;

    
    if (sigaction(SIGINT, &act, NULL) < 0)
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
