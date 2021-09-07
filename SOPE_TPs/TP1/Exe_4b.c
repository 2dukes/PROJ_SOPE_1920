#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

int main(int argc, char* argv[])
{
    // char toConcat[100] = "";
    char* toConcat = malloc(MAX_LEN * sizeof(char));
    int hiNum;
    
    // printf("%d\n", argc);
    
    for(int i = 1; i < argc; i++)
    {
        if(atoi(argv[i]) != 0) // Returns 0 if not succeded!
            hiNum = atoi(argv[i]);

        strcat(toConcat, argv[i]);
        char space[] = " ";
        strcat(toConcat, space);
    }

    for(int i = 0; i < hiNum; i++)
        printf("Hello %s!\n", toConcat);

    return 0;
}