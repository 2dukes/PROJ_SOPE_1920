#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

int main(int argc, char* argv[], char* envp[])
{
    char userName[MAX_LEN];
    while(*envp != NULL)
    {
        if(strncmp(*envp, "USERNAME=", 9) == 0)
        {
            strcpy(userName, *envp);
            printf("%s\n", userName);
        }    
        envp++;
    }

    // Using strtok -> https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split
    char delim[] = "=";
    char *ptr = strtok(userName, delim);
    ptr = strtok(NULL, delim);
    printf("%s\n", ptr); // Prints whitelizard in USERNAME=whitelizard

    printf("Hello %s !\n", ptr);
    return 0;
}