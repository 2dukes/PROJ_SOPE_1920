#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdbool.h>

char SEM_NAME[] = "/Exe4Semaphore";
char SHM_NAME[] = "/Exe4SharedMemory";
char SHM_POS[] = "/Exe4Pos";
char SHM_VALUE[] = "/Exe4Value";

int main(int argc, char * argv[]) { 
    /* 
        Without error verification -> Some processes main not appear as they can end first... (Memory mapping gives error not processed)
        In this case the number of written chars is of course = 0.
    */
   
    int npos = atoi(argv[1]);
    int numsWritten = 0;

    int shmFd = shm_open(SHM_NAME, O_RDWR, 0600); 
    int shmPosFd = shm_open(SHM_POS, O_RDWR, 0600);
    int shmValueFd = shm_open(SHM_VALUE, O_RDWR, 0600);

    int *pos = (int *) mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmPosFd, 0); 
    int *val = (int *) mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmValueFd, 0);
    int *buf = (int *) mmap(0, npos * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0); 

    sem_t *sem = sem_open(SEM_NAME, 0, 0600, 0);
    while(true) {
        sem_wait(sem); // Semaphore acts like a mutex..

        if(*pos >= npos) {
            sem_post(sem);
            break;
        }

        buf[*pos] = *val;

        *pos = *pos + 1;
        *val = *val + 1;
        
        sem_post(sem);
        numsWritten++;
    }    
    
    sem_close(sem);
    munmap(buf, npos * sizeof(int));
    munmap(pos, sizeof(int));
    munmap(val, sizeof(int));
    printf("Numbers Written: %d (%d)\n", numsWritten, getpid());

    return 0;
}