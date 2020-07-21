#include <stdio.h>
#include <string.h>


#define MAX_LEN 256

int main()
{
    char command[MAX_LEN];
    fgets(command, MAX_LEN, stdin);
    char tokens[MAX_LEN][MAX_LEN];
    int index = 0;

    char delim[] = ";|";
    char *ptr = strtok(command, delim);
    strcpy(tokens[index++], ptr);
    // printf("%s\n", ptr);

    while((ptr = strtok(NULL, delim)) != NULL)
    {
        // printf("%s\n", ptr);
        strcpy(tokens[index++], ptr);
    }    
    
    for(int i = 0; i < index; i++)
        printf("%s\n", tokens[i]);

    // It prints the second commands with a space at the beggining.
}