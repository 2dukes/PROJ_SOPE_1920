#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

int main(int argc, char* argv[], char* envp[])
{
    while(*envp != NULL)
        printf("%s\n", *(envp++));  
    return 0;
}