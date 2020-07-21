#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 1000

void * printThread(void * arg) {
    sleep(1);
    printf("Started Thread %ld\n", pthread_self());

    void * result = malloc(sizeof(int));
    *(int *) result = *(int *) arg;
    return result;
}

int main() {
    
    pthread_t threadID[NUM_THREADS];
    int orderNum[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++) {
        orderNum[i] = i;
        pthread_create(&threadID[i], NULL, printThread, &orderNum[i]);
    }

    void * result;
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threadID[i], &result);
        printf("Thread %d ended!\n", *(int *) result);
    }

    // pthread_exit(NULL);
    exit(0); // Ends other threads abruptly...
}









/*

a) Escreva um programa que crie N novas threads. Cada thread deve "dormir" durante    um segundo,
escrever a sua TID e terminar retornando um número inteiro igual ao seu número de ordem (1..N) que lhe
deve ser passado com parâmetro

*/