// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 10000

void * thrfunc(void * arg)
{
    int i;
    // fprintf(stderr, "Starting thread %s\n", (char *) arg);
    fprintf(stderr, "Starting thread %d\n", *(int *) arg);
    for (i = 1; i <= NUMITER; i++) {
        printf("%d", *(int *)arg);
        fflush(stdout);
    }     
    // write(STDERR, arg,1);
    return NULL;
}
int main()
{
    pthread_t ta, tb;

    // char first = '1', second = '2';
    int first = 1, second = 2;
    pthread_create(&ta, NULL, thrfunc, &first);
    pthread_create(&tb, NULL, thrfunc, &second);

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
} 

/* THe main problem while passing the same variable to the threads is: if the variable is altered in some of the threads, it might cause inconsistent output in other/same thread(s). */