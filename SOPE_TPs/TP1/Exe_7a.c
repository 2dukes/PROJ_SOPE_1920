#include <stdio.h>
#include <stdlib.h>

static void exitHandler1(void)
{
    exit(0); // Termina o handler...
    printf("Executing exit handler 1\n");
}

static void exitHandler2(void)
{
    printf("Executing exit handler 2\n");
}

// int atexit(void (*func) (void));

int main(void)
{
    int value1 = atexit(exitHandler1); // Retrieves an integer value.
    int value2 = atexit(exitHandler2);

    if (value1 != 0 || value2 != 0) { 
        printf("atexit () function registration failed\n"); 
        exit(1); 
    } 
    // atexit(exitHandler2); -> b) -> É sim possível fazer mais do que uma vez o registo desses handlers.

    // atexit functions are executed on the reverse order as they we're referenced.
    // So first is exitHandler2, and then exitHandler1 : QUEUE

    // abort(); -> b) -> Ao executar abort, nada mais é executado, e consecutivamente nenhum dos handlers, uma vez que o programa sai abrutamente.
    printf("Main done!\n");
    exit(0);
}