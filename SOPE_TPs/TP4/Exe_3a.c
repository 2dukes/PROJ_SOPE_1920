#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>

int v = 0;


void SIGUSR_handler(int signo) {
    if(signo == SIGUSR1)
        v++;
    else if(signo == SIGUSR2)
        v--;
}

int main(void) {
    struct sigaction action;

    action.sa_handler = SIGUSR_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if(sigaction(SIGUSR1, &action, NULL) < 0) {
        fprintf(stderr,"Unable to install SIGUSR1 handler\n");
        exit(1);
    }
    if(sigaction(SIGUSR2, &action, NULL) < 0) {
        fprintf(stderr,"Unable to install SIGUSR2 handler\n");
        exit(1);
    }

    char aux[8];
    while(true) {
        sleep(1);
        sprintf(aux, "%d", v);
        write(STDOUT_FILENO, aux, strlen(aux));
    }

    return 0;
}