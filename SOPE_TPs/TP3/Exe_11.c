#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <wait.h>

#define BUF_SIZE 256

int main(int argc, char *argv[], char *envp[])
{
    char cmd[BUF_SIZE]; 
    pid_t pid;
    int  status, index;
    bool redirectOutput;
    char delim[] = " ";
    char* arguments[50];
    char filename[BUF_SIZE];

    do
    {
        write(STDOUT_FILENO, "minish > ", strlen("minish > "));
        fgets(cmd, BUF_SIZE, stdin); // fgets retains the \n
        cmd[strlen(cmd) - 1] = '\0';

        index = 0;
        redirectOutput = false;
        // ls -o file.txt
        for(char *ptr = strtok(cmd, delim); ptr != NULL; ptr = strtok(NULL, delim))
        {
            if(redirectOutput) {
                strcpy(filename, ptr);
                break;
            }
            else if(strcmp(ptr, "-o") == 0)
                redirectOutput = true;
            else
            {
                arguments[index] = (char*) malloc(BUF_SIZE);
                strcpy(arguments[index++], ptr); 
            }    
        }
        if((pid = fork()) == 0) // Filho
        {
            if(redirectOutput) // Output -> FILE
            {
                int fd = open(filename, O_WRONLY | O_SYNC | O_CREAT | O_EXCL | O_TRUNC, 0600);
                if(fd != -1)
                    dup2(fd, STDOUT_FILENO);
                else 
                {
                    write(STDERR_FILENO, "Selected file already exists...\n\n", strlen("Selected file already exists...\n\n"));
                    exit(1);
                }
            }

            arguments[index] = NULL;
            execvp(arguments[0], arguments);
            if(strcmp(cmd, "quit") != 0) {
                write(STDERR_FILENO, "Something went wrong...\n\n", strlen("Something went wrong...\n\n"));
                exit(1);
            }    
        }
        else
        {
            wait(&status);                
        }

    } while(strcmp(cmd, "quit") != 0);
}