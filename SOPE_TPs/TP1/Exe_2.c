#include <stdio.h>
int hs(void)
{
    printf("Hello !\n");
    return 0;
}

// a) gcc -Wall -o Exe2 Exe_2.c

/* 

b) /usr/bin/ld: /usr/lib/gcc/x86_64-linux-gnu/8/../../../x86_64-linux-gnu/Scrt1.o: in function `_start':
(.text+0x20): undefined reference to `main'
collect2: error: ld returned 1 exit status

*/

/* Exercício 3:

a) | b) echo $? -> * Mostra o código de retorno do último comando executado *
Se o código estiver correto, dá 0 (Sucesso). Caso haja a substituição do nome da função main,
dá return 1 (Erro).

c) ls -> Como foi executado com sucesso, dá return 0.

/*