#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

int main(int argc, char* argv[], char* envp[])
{
    char pathVar[] = "USERNAME";
    printf("Username: %s\n", getenv(pathVar));
    
    return 0;
}