#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <wait.h>

#define MAXELEMS 10000000 // nr. max de posicoes
#define MAXTHREADS 100 // nr. max de threads
#define min(a, b) (a)<(b)?(a):(b)

char SEM_NAME[] = "/Exe4Semaphore";
char SHM_NAME[] = "/Exe4SharedMemory";
char SHM_POS[] = "/Exe4Pos";
char SHM_VALUE[] = "/Exe4Value";

void verify(int npos, sem_t* sem, int* buf, int* pos) {
    int k = 0;

    while(k < npos) {
        sem_wait(sem);
        if(k < *pos) {
            if(buf[k] != k) 
                printf("ERROR: buf[%d] = %d\n", k, buf[k]);
            k++;
        }
        sem_post(sem);
    }
}

int main(int argc, char *argv[]) {
    int npos;    
    int nthr;

    if (argc != 3) {
        printf("Usage: %s <nr_pos> <nr_thrs>\n",argv[0]);
        return 1;
    } 

    npos = min(atoi(argv[1]), MAXELEMS);   // no. efectivo de posicoes
    nthr = min(atoi(argv[2]), MAXTHREADS); // no. of processes to launch

    // Shareds memory creation -> O_RDWR = Read and Write... + CREATE (O_CREAT)
    int shmFd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0600); 
    int shmPosFd = shm_open(SHM_POS, O_CREAT | O_RDWR, 0600);
    int shmValueFd = shm_open(SHM_VALUE, O_CREAT | O_RDWR, 0600);

    ftruncate(shmPosFd, sizeof(int));
    ftruncate(shmValueFd, sizeof(int));
    
    if(shmFd < 0) {
        printf("An error occured while creating shared memory!\n");
        exit(1);
    }

    if(ftruncate(shmFd, npos * sizeof(int)) < 0) {
        printf("An error was raised while allocating space!\n");
        exit(1);
    }

    // Attach pos & val without error verification
    int *pos = (int *) mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmPosFd, 0); 
    int *val = (int *) mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmValueFd, 0);

    // Attach this region to virtual memory (BUFFER)
    int *buf = (int *) mmap(0, npos * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0); // Last parameter is the offset!
    if(buf == MAP_FAILED) {
        printf("An error occured while attaching region...\n");
        exit(1);
    }

    // Create & Initialize semaphore
    sem_t *sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0600, 1);
    if(sem == SEM_FAILED) {
        printf("An error occurred while creating the semaphore!\n");
        exit(1);  
    }

    // Launch processes...
    for (int k=0; k < nthr; k++) { 
        pid_t toFork;
        char nPosString[19];
        sprintf(nPosString, "%d", npos);
        
        if((toFork = fork()) == 0) {
            execl("/home/whitelizard/Desktop/TP7/Exe_4_Process", "/home/whitelizard/Desktop/TP7/Exe_4_Process", nPosString, NULL);
            printf("Hope it didn't fail!\n");
            exit(2);   
        }
        
    }

    verify(npos, sem, buf, pos);

    for(int k=0; k < nthr; k++) 
        wait(NULL);

    sem_close(sem);
    sem_unlink(SEM_NAME);

    if(munmap(buf, npos * sizeof(int)) < 0) {
        printf("Error on unmap!\n");
        exit(1);
    }

    if(shm_unlink(SHM_NAME) < 0) {
        printf("Error on shm_unlink...\n");
        exit(1);
    }

    munmap(pos, sizeof(int));
    munmap(val, sizeof(int));
    shm_unlink(SHM_POS);
    shm_unlink(SHM_VALUE);

    exit(0);
} 