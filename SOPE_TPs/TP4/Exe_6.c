#define _POSIX_SOURCE

#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

pid_t pid;

void sigalrm_handler(int signo) {

    kill(pid, SIGKILL); // Kill child process... Doesn't raise a SIGCHLD...
    printf("Forced termination!\n");

    exit(0); // If we didn't have exit(0) and we we're not blocking SIGCHLD, what would happen is that when the handler is finished, the SIGCHLD that was
    // blocked is now handled by sigchld_handler(); As we don't want that, we end the program right here.
}

void sigchld_handler(int signo) {
    printf("Normal termination!\n");
    exit(0);
}

int main(int argc, char* argv[])
{
    if(argc < 4) {
        printf("Usage: limit N prog progArg1 [progArg2 ...]");
        exit(1);
    }
    if((pid = fork()) < 0) {
        printf("An Error occurred while creating the subprocess...\n");
        exit(2);
    }
    if(pid == 0) { // Filho
        char filename[100];
        sprintf(filename, "/home/whitelizard/Desktop/TP4/%s", argv[2]);
        execv(filename, &argv[2]);
        printf("Execution problem...\n");
        exit(0);
    }
    else { // Pai
        struct sigaction action;

        action.sa_flags = 0;
        action.sa_handler = sigalrm_handler; 
        sigemptyset(&action.sa_mask);
        sigaddset(&action.sa_mask, SIGCHLD); // Blocks SIGCHLD while executing SIGALRM handler.
        sigaction(SIGALRM, &action, NULL); // Sets sigalrm_handler to handle SIGALRM.

        action.sa_handler = sigchld_handler;
        sigemptyset(&action.sa_mask);
        sigaddset(&action.sa_mask, SIGALRM); // Blocks SIGALRM while executing SIGCHLD handler.
        sigaction(SIGCHLD, &action, NULL); // Sets sigchld_handler to handle SIGCHLD.

        sigfillset(&action.sa_mask);
        sigdelset(&action.sa_mask, SIGALRM); // Block ALL but SIGALRM
        sigdelset(&action.sa_mask, SIGCHLD); // Block ALL but SIGCHLD   

        alarm(atoi(argv[1])); // Starts the alarm given N seconds...

        sigsuspend(&action.sa_mask); // Waits for SIGALRM or SIGCHLD
        
    }
    return 0;
}