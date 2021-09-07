#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2

int numCharsGLobal = 50000;

void * thrfunc(void * arg)
{
    void * numChars;
    numChars = malloc(sizeof(int));

    fprintf(stderr, "Starting thread %s\n", (char *) arg);

    while(numCharsGLobal > 0) {
        numCharsGLobal--;
        write(STDERR, arg, 1);
        *((int *) numChars) += 1;
        printf("Hello\n");
    }     
    
    return numChars;
}
int main()
{
    pthread_t ta, tb;
    void * res1;
    void * res2;

    char first = '1', second = '2';

    pthread_create(&ta, NULL, thrfunc, &first);
    pthread_create(&tb, NULL, thrfunc, &second);    

    pthread_join(ta, &res1);
    pthread_join(tb, &res2);

    printf("Thread 1: %d\n", *(int *) res1);
    printf("Thread 2: %d\n", *(int *) res2);
    printf("NumCharsWritten: %d\n", *(int *) res1 + *(int *) res2);

    free(res1);
    free(res2);

    return 0;
} 

/* Because both threads acess the same Global variable, if one gets stucked inside numCharsGLobals-- the other can produce inconsistent output. */