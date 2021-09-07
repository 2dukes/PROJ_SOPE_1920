// PROGRAMA p02a.c
#define _POSIX_SOURCE

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo)
{
    printf("Entering SIGINT handler ...\n");
    sleep(10);
    printf("Exiting SIGINT handler ...\n");
} 

void sigterm_handler(int signo) 
{
    printf("Entering SIGTERM handler ...\n");
    sleep(10);
    printf("Exiting SIGTERM handler ...\n");
}

int main(void)
{
    struct sigaction action;
    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGINT,&action,NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGINT handler\n");
        exit(1);
    }
    action.sa_handler = sigterm_handler;
    if(sigaction(SIGTERM, &action, NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGTERM handler\n");
        exit(1);
    }
    printf("Try me with CTRL-C ...\n");

    while(1) pause();
    exit(0);
} 

/* 

Question A -> 
If we type CTRL-C several times during execution, one will be executed and there will be another CTRL+C pending in a queue. 
After the first one is ended, the second one will come and the rest will be ignored, as the OS only registers 1 pending signal per type.

So, everytime we leave the pause(), as we're in a while(true) loop, the program will be waiting for another non-ignored signal to leave the pause()
and then get back to it. It's basically a loop.

*/

/*

Question B ->
If we send a kill command with a SIGTERM to the program, the pause() will have no affect, as the program will suddently end because SIGTERM is not handled.
"Ação por omissão é terminação" JAS 2020

*/

/*

Question C ->

There are many different situations. For example, if we launch a SIGTERM and right after another SIGTERM, the program will compute the first one, and after that 
one ends, it will compute the other one (separately). But if we have SIGTERM and in the middle SIGINT, or the opposite, the first SIG handler will be interrupted
by the second SIG handler. If in that process we repeat again the signals, one of each type will be left in a queue and they will get executed after that.

*/