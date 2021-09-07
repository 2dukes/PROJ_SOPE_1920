#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>


int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    int status;

    if (argc != 2) {
        printf("usage: %s dirname\n",argv[0]);
        exit(1);
    }

    pid=fork();

    if (pid > 0) // Father
    {
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
        wait(&status);
        if(WIFEXITED(status))
        {
            printf("%ld exited with return code %d\n",
                (long)pid, WEXITSTATUS(status));
        }
        /* was the child terminated by a signal? */
        else if (WIFSIGNALED(status))
        {
            printf("%ld terminated because it didn't catch signal number %d\n",
                (long)pid, WTERMSIG(status));
        }
    }    
    else if (pid == 0) { // Son
        // execlp("ls", "ls", "-laR", argv[1], NULL);
        
        // which ls -> /usr/bin/ls
        // execl("/usr/bin/ls", "ls", "-laR", argv[1], NULL);

        char* arguments[] = {"ls", "-laR", argv[1], NULL};
        // execvp("ls", arguments);
        // execv("/usr/bin/ls", arguments);
        execve("/usr/bin/ls", arguments, envp); // Same environment variables as the father...
        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}

/*
With Existing directory: Exit Code = 0
With Unexisting directory: Exit Code = 2 -> Errno indicating "No such file or directory"
Kill case...
The program is abnormally ended. As a consequence it enters WIFSIGNALED, as it couldn't 
handle a signal (9 = SIGKILL). In case you don't use those ifs, the exit code is 0.
*/