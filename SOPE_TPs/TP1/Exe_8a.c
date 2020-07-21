#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    struct tms t;
    clock_t dub;
    int tics_per_second = sysconf(_SC_CLK_TCK); // #include <unistd.h> to use _SC_CLK_TCK
    srand(time(NULL));

    int supLim = atoi(argv[1]);
    int selNum = atoi(argv[2]);
    int choice = rand() % supLim;
    int iter = 1;
    printf("Iteration: 0 -> %d\n", choice);
    while(choice != selNum)
    {
        choice = rand() % supLim;
        printf("Iteration: %d -> %d\n", iter, choice);
        iter++;
    }

    dub = times(&t);
    
    printf("TPS: %d\n", tics_per_second);
    printf("Elapsed time: %ld\n", (dub / tics_per_second)); // In seconds
    printf("System time: %ld\n", t.tms_stime); // In ticks...
    printf("User time: %ld\n", t.tms_utime); // Also in ticks...

    /* Execute with large numbers, like... ./Exe8 1000000 2
    exit(0);
}