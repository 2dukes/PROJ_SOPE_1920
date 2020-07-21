#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* int main(void) {
    write(STDOUT_FILENO, "1", 1);
    if(fork() > 0) 
    {
        write(STDOUT_FILENO, "2", 1);
        write(STDOUT_FILENO, "3", 1);
    }
    else
    {
        write(STDOUT_FILENO, "4", 1);
        write(STDOUT_FILENO, "5", 1);
    }
    write(STDOUT_FILENO, "\n", 1);
    return 0;
} */

/*

a)
--> Se o processo pai executar primeiro:
123
45
--> Se o processo filho executar primeiro:
145
23
b)
--> Output do programa:
123
45
--> Conclui-se assim que o processo pai executou primeiro.
c)
--> Output do programa:
123
145

*/


/* Em geral, não se sabe quem continua a executar imediatamente após uma chamada a fork() (se é o pai ou o filho).
Depende do algoritmo de escalonamento. */


// c) With 'write', writes 123\n45\n ... with 'printf', writes 123145.

/* 

Inicialmente o buffer do processo pai é igual ao do processo filho e contém um '1'.
Isto acontece porque ele nunca é esvaziado antes da chamada fork. E o buffer de Output
é 'herdado' pelo filho. Desta forma aparecem dois '1' quando se corre com printfs e apenas um '1',
quando se corre com write, pois a seguir a cada write, o buffer de saída é esvaziado, uma vez que
a informação é apresentada logo no ecrã.


--> A função printf, ao contrário da chamada ao sistema write, acumula o que irá escrever no ecrã num buffer.
Esse buffer só é despejado quando se encontra um carácter '\n' ou quando se chama a função fflush(stdout).
Neste programa, primeiro chama-se printf("1"), pelo que o 1 fica no buffer do stdout. Depois é executado o processo
pai e chega-se a um printf("\n"), pelo que o buffer é despejado, gerando-se o output "123". A seguir disso, é
executado o processo-filho, mas no buffer do stdout ainda se encontra o "1", já que o buffer apenas foi despejado no
processo-pai. Portanto, o buffer só é despejado quando o processo filho encontra um "\n", gerando-se o output "145".
*/



int main(void) {
    printf("1");
    if(fork() > 0) 
    {
        printf("2");
        printf("3");
    }
    else
    {
        printf("4");
        printf("5");
    }
    printf("\n");
    return 0;
}

/* 

d)
--> Output do programa:
1
23
45
--> Seguindo a explicação da alínea c, como o printf("1\n") no início do programa tem um carácter '\n', o buffer
do stdout é despejado.

*/