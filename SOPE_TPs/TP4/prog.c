#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    
    if(argc < 2)
        printf("Usage: prog ARG1 [ARGN ...] \n");
    
    for(int i = 1; i <= 6; i++)
    {
        printf("%s\n", argv[1]);
        sleep(5);   
    }

    return 0;
}