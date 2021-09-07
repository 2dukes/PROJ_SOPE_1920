// PROGRAMA p04a.c
#define _POSIX_SOURCE

#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void sigchld_handler(int signo) {
    int status;
    pid_t pid = wait(&status);

    if (pid != -1)
        printf("PARENT: child with PID=%d terminated with exit code %d\n",pid,WEXITSTATUS(status));
}

int main(void)
{
    pid_t pid;
    int i, n;

    for (i=1; i<=10; i++) {
        pid=fork(); 

        if (pid == 0){
            printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
            sleep(15); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
            exit(0);
        }
    }

    struct sigaction action;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    action.sa_handler = sigchld_handler;

    sigaction(SIGCHLD, &action, NULL); // Ignoring SIGCHLD prevents child processes of becoming Zombies...

    for (i=1 ;i<=10; i++) {

        printf("PARENT: working hard (task no. %d) ...\n",i);
        n=20; while((n=sleep(n))!=0); // WHen SIGCHILD is sent, has no handler is installed, the signal is ignored hence sleep() is not interrupted.
        printf("PARENT: end of task no. %d\n",i);
        printf("PARENT: waiting for child no. %d ...\n",i);

    }
    exit(0);
}