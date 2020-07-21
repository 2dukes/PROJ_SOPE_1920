#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct operationNum {
    int num[2];
    char op;
};

struct result {
    int num;
    char op;
};

void * executeOp(void * arg) {
    struct operationNum* toReceive = (struct operationNum *) arg;
    void * result = malloc(sizeof(struct result));

    if(toReceive->op == '+')
        ((struct result *) result)->num = toReceive->num[0] + toReceive->num[1];
    else if(toReceive->op == '-')
        ((struct result *) result)->num = toReceive->num[0] - toReceive->num[1];
    else if(toReceive->op == '*')
        ((struct result *) result)->num = toReceive->num[0] * toReceive->num[1];
    else if(toReceive->op == '/')
        ((struct result *) result)->num = toReceive->num[0] / toReceive->num[1];

    return result;
}

int main() {
    
    struct operationNum toBuild[4];
    pthread_t threadID[4];
    void * result;
    int num1, num2;

    scanf("%d %d", &num1, &num2);
    
    // Could be simplified with an array of operations!
    toBuild[0].num[0] = num1;
    toBuild[0].num[1] = num2;
    toBuild[0].op = '+';
    pthread_create(&threadID[0], NULL, executeOp, (void * ) &toBuild[0]);

    toBuild[1].num[0] = num1;
    toBuild[1].num[1] = num2;
    toBuild[1].op = '-';
    pthread_create(&threadID[1], NULL, executeOp, (void * ) &toBuild[1]);

    toBuild[2].num[0] = num1;
    toBuild[2].num[1] = num2;
    toBuild[2].op = '*';
    pthread_create(&threadID[2], NULL, executeOp, (void * ) &toBuild[2]);

    toBuild[3].num[0] = num1;
    toBuild[3].num[1] = num2;
    toBuild[3].op = '/';
    pthread_create(&threadID[3], NULL, executeOp, (void * ) &toBuild[3]);

    for(int i = 0; i < 4; i++) {
        pthread_join(threadID[i], &result);
        printf("Result of operation '%c' : %d\n", ((struct result*) result)->op, ((struct result*) result)->num);
    }

    return 0;
}


/*

a) Escreva um programa que leia 2 números do teclado e crie 4 threads que façam, respectivamente, a
soma, a subtracção, o produto e o quociente dos números lidos. Os operandos devem ser passados como
parâmetros às threads (usar duas formas diferentes de o fazer, através de um array e de uma struct ). O
valor dos operandos e o resultado de cada operação devem ser apresentados no ecrã pela thread que
executou cada operação.

b) Alterar o programa anterior por forma a que os resultados sejam apresentados pela main thread.  

*/