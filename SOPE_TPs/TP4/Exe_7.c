#define _POSIX_SOURCE

#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

int main(int argc, char* argv[]) {

    pid_t* pid = calloc((argc - 1), sizeof(pid_t));
    int index = 1;
    int pid_index = 0;
    while(argv[index] != NULL) {
        
        if((pid[pid_index++] = fork()) == 0)
        {
            execlp(argv[index], argv[index], NULL);
            printf("An error occurred while executing: %s\n", argv[index]);
            exit(1);
        }
        index++;
    }

    int status;
    pid_t termPid;

    for(int i = 0; i < (argc - 1); i++) {
        termPid = wait(&status);
        if(termPid == -1)
            printf("\nPID: %d exited with Code: %d\n", termPid, WEXITSTATUS(status));
        if(WEXITSTATUS(status) != 0) // Send signal to kill all childs...
        {
            for(int j = 0; j < (argc - 1); j++) 
            {
                if(pid[j] != termPid) {
                    kill(pid[j], SIGKILL);
                    printf("Killed: %d\n", pid[j]);
                }
            }
        }
    }

    return 0;
}