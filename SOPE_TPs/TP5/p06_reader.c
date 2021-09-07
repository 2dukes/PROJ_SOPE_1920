// PROGRAMA p06_reader.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>
#include <string.h> 

int readline(int fd, char *str);

int main(void)
{
    int fd;
    char str[100];

    mkfifo("/tmp/myfifo",0660);
    fd=open("/tmp/myfifo", O_RDONLY);

    while(readline(fd,str)) printf("%s",str);

    close(fd);
    return 0;   
}

int readline(int fd, char *str)
{
    int n;

    do {
        n = read(fd,str,1);
    } while (n>0 && *str++ != '\0');

    return (n>0);
} 

/*

b) Como pôde verificar o processo‐leitor termina assim que o processo‐escritor terminar. Explique por que
é que isso acontece (sugestão: o que é que a chamada read() devolve quando o terminal de escrita do
FIFO for fechado pelo processo‐escritor ?). Altere o programa‐leitor por forma a abrir o FIFO em modo de
leitura e escrita. Volte a executar os programas e interprete o que acontecer. Qual a dificuldade que surgiu?
Na prática, haverá alguma diferença entre fazer uma única chamada open() para abrir o FIFO em modo
de leitura e escrita ou fazer duas chamadas, uma para leitura e outra para escrita ?

R1: O read devolve 0 quando o terminal de escrita se fechar, fazendo com que o loop seja interrompido.

- read() de um Pipe/FIFO vazio, não aberto para escrita
» retorna 0 (end of file), independentemente de O_NONBLOCK

R2: Como o FIFO é aberto para escrita e para leitura, o read nunca retornará 0, porque o terminal de escrita nunca é fechado, uma vez
que está sempre aberto, tal como o terminal de leitura. Desta forma, a read fica à espera de um novo valor.

*/