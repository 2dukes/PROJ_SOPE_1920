// PROGRAMA p04a.c
#define _POSIX_SOURCE

#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>



int main(void)
{
    pid_t pid;
    int i, n;

    for (i=1; i<=3; i++) {
        pid=fork(); 

        if (pid == 0){
            printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
            sleep(i*7); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
            exit(0);
        }
    }

    struct sigaction action;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    action.sa_handler = SIG_IGN;

    sigaction(SIGCHLD, &action, NULL); // Ignoring SIGCHLD prevents child processes of becoming Zombies...

    for (i=1 ;i<=4; i++) {

        printf("PARENT: working hard (task no. %d) ...\n",i);
        n=20; while((n=sleep(n))!=0); // WHen SIGCHILD is sent, has no handler is installed, the signal is ignored hence sleep() is not interrupted.
        printf("PARENT: end of task no. %d\n",i);
        printf("PARENT: waiting for child no. %d ...\n",i);

    }
    exit(0);
}

/*

Question 1 -> Ação por omissão associada a SIGCHLD é ignorar. DÚVIDA...

Question B -> Neste caso, dado que todos os processos demorariam o mesmo tempo a terminar, o que iría acontecer era:
o pai iria receber 15 SIGCHLD ao mesmo tempo, sendo que só iria processar o primeiro, e depois outro (apenas é registado um sinal pendente).
Logo irão haver vários processos zombies pendentes...

*/