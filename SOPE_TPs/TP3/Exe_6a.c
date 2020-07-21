#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int main(void)
{
    pid_t pid;
    int i, j;
    int status; // Added for b)
 
    printf("I'm process %d. My parent is %d.\n", getpid(),getppid());
    for (i=1; i<=20; i++) 
    {
        pid = fork();
        if ( pid < 0) {
            printf("fork error");
            exit(1);
        }
        else if (pid == 0) { // Filho
            printf("I'm process %d. My parent is %d. I'm going to work for 1 second ...\n",
                getpid(),getppid());

            sleep(1); // simulando o trabalho do filho
            printf("I'm process %d. My parent is %d. I finished my work\n", getpid(),getppid());
            
            // exit(0); // a eliminar na alinea c)
        }
        else // simulando o trabalho do pai
        { 
            for (j=1; j<=10; j++) {
                waitpid(pid, &status, WNOHANG); // Added for b)
                sleep(1);
                printf("father working ...\n");
            }
        }
    }    
    exit(0);
} 

/*
Os processos criados, tornam-se zombies, enquanto o pai não termina... Isso acontece 3x,
pois são criados 3 processos. APós o pai terminar, eles são imediatamente adotados e terminados
pelo init/upstart/... e deixam de aparecer como 'defunct'.
*/

/*
Caso o exit(0) seja eliminado, irá ser criada uma série de processos, de forma recursiva,
uma vez que cada filho irá criar no máximo mais 2 processos, consoante o valor de i do ciclo for.
*/