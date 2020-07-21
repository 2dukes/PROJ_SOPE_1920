// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHello(void *threadnum)
{
    printf("Hello from thread no. %d!\n", *(int *) threadnum);
    pthread_exit(NULL);
}
int main()
{
    pthread_t threads[NUM_THREADS];
    int t, threadCount[NUM_THREADS];

    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %d\n", t);
        threadCount[t] = t;
        pthread_create(&threads[t], NULL, PrintHello, &threadCount[t]);
    }

    // pthread_exit(0);
    exit(0);
}

/* Results are due to passing a (void *) &t, which means, passing variable t as a pointer.
If so then other threads could use that value which is not was it as meant to be. For that reason, we saw repeated values on the sheet's result (Race condition). */

/* If we make an exit call at the end of the main thread, then all the threads end up immediately, causing inexpected output. */