#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if (argc != 2 && argc != 3) {
        printf("usage: %s dirname [destination]\n",argv[0]);
        exit(1);
    }

    if(argc == 3)
    {
        int fd = open(argv[2], O_WRONLY | O_SYNC | O_CREAT | O_EXCL | O_TRUNC, 0600);
        dup2(fd, STDOUT_FILENO);
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
Pretende‐se que o programa do problema 8 possa a aceitar, na linha de comando, um segundo argumento,
opcional, indicando o nome de um ficheiro onde o utilizador pretende guardar a listagem gerada pelo
processo‐filho. Se este argumento for fornecido, o ficheiro deve ser criado pelo processo‐filho e a standard
output do processo‐filho deve ser redireccionada para esse ficheiro, antes de executar a chamada exec.
Proceda às alterações necessárias ao programa 8, por forma a cumprir este objectivo.
*/