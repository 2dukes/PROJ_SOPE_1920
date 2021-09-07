#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int global=0;

void *thr_func(void *arg)
{
    while(global++ < 20) {
        printf("t%d - %d\n", * (int *) arg, global); sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t tid1, tid2;
    int t1=1, t2=2;

    printf("Hello from main thread\n");
    pthread_create(&tid1, NULL, thr_func, &t1);
    pthread_create(&tid2, NULL, thr_func, &t2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}