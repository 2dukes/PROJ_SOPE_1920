#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>
#include <time.h>

int v = 0;

void SIGUSR_handler(int signo) {
    if(signo == SIGUSR1)
        v++;
    else if(signo == SIGUSR2)
        v--;

    char aux[8];

    sprintf(aux, "%d\n", v);
    write(STDOUT_FILENO, aux, strlen(aux)); 
}

int main(void) {
    pid_t pid;
    pid = fork();
    int status;

    if(pid == 0) { // Filho
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
        
        sigfillset(&action.sa_mask);
        sigdelset(&action.sa_mask, SIGUSR1);
        sigdelset(&action.sa_mask, SIGUSR2);

        for(int i = 1; i <= 50; i++) {
            // printf("Hello\n");
            sigsuspend(&action.sa_mask); // Only accepts SIGUSR1 and SIGUSR2
            
        }    
           
        exit(0);
    }
    else {
        srand(time(NULL));
        sleep(1); // Wait for child to install handlers otherwise child could terminate inexpectedly...
        int r;
        
        for(int i = 1; i <= 50; i++)
        {
            r = rand() % 2;
            if(r == 0)
                kill(pid, SIGUSR1);
            else kill(pid, SIGUSR2);
            sleep(1); // Time between signals... It could be too fast otherwise...
        }

        wait(&status);
    }

    return 0;
}