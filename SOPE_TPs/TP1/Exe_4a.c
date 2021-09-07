#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

int main(int argc, char* argv[])
{
    // char toConcat[100] = "";
    char* toConcat = malloc(MAX_LEN * sizeof(char));
    // printf("%d\n", argc);
    for(int i = 1; i < argc; i++)
    {
        strcat(toConcat, argv[i]);
        char space[] = " ";
        strcat(toConcat, space);
    }
    printf("Hello %s!", toConcat);
    return 0;
}