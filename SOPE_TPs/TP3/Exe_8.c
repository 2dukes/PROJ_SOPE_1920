#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if (argc != 2) {
        printf("usage: %s dirname\n",argv[0]);
        exit(1);
    }

    pid=fork();

    if (pid > 0) // Father
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
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
Alínea a)
O programa executa o comando ls para o diretório especificado em argv[1].
*/