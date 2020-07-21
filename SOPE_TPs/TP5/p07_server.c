#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXLINE 128

struct toReceive
{
    int num1;
    int num2;
    char op;
};

int main() {
    mkfifo("/tmp/towerController", 0660);
    mkfifo("/tmp/clientFifo", 0660);

    int towerController = open("/tmp/towerController", O_RDONLY);
    int clientManager = open("/tmp/clientFifo", O_WRONLY);

    int rBytes;    
    char result[MAXLINE];
    struct toReceive infOp;

    while((rBytes = read(towerController, &infOp, sizeof(infOp)) != 0)) {
        if(infOp.num1 == 0 && infOp.num2 == 0)      
            break;

        switch (infOp.op)
        {
            case '+': // Sum
                sprintf(result, "%d", infOp.num1 + infOp.num2);
                break;    
            case '-': // Subtract 
                sprintf(result, "%d", infOp.num1 - infOp.num2);
                break;
            case '*': // Product 
                sprintf(result, "%d", infOp.num1 * infOp.num2);
                break;
            case '/': // Division 
                sprintf(result, "%f", (double) infOp.num1 / infOp.num2);
                break;
        }
        write(clientManager, result, strlen(result) + 1);
    }
    
    close(towerController);
    close(clientManager);
    unlink("/tmp/towerController");
    unlink("/tmp/clientFifo");
    return 0;
}



/* Resolva o problema 2 usando dois FIFOS com os nomes fifo_req e fifo_ans para a comunicação;
fifo_req é o FIFO através do qual os pedidos devem ser enviados ao processo‐calculador e fifo_ans é
o FIFO através do qual este processo devolve os resultados. Neste caso, os dois processos, o que lê os
números e apresenta os resultados dos cálculos (cliente) e o que faz estes cálculos (servidor) serão
processos independentes, cujos executáveis poderão chamar‐se, por exemplo, p07_client e
p07_server. O processo‐servidor deve manter‐se em funcionamento até que os números a processar
sejam ambos iguais a zero, situação em que não deve efectuar qualquer cálculo, mas apenas deve destruir
os dois FIFOS. Desta forma torna‐se possível que múltiplos clientes solicitem a execução de cálculos. Os
FIFOS devem ser criados no directório /tmp pelo servidor. */