#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int numCharsGLobal = 50000;

void * thrfunc(void * arg)
{
    void * numChars;
    numChars = malloc(sizeof(int));

    fprintf(stderr, "Starting thread %s\n", (char *) arg);

    while(numCharsGLobal > 0) {

        pthread_mutex_lock(&mut);
        numCharsGLobal--;
        pthread_mutex_unlock(&mut);
        
        write(STDERR, arg, 1);
        *((int *) numChars) += 1;

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

/* Solved issue of sheet nº6 using mutexes! */