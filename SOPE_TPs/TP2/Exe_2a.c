#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <source> <destination>", argv[0]);
        return 1;
    }
    
    FILE* src;
    src = fopen(argv[1], "r");
    if(src == NULL)
    {
        perror(argv[1]);
        return 2;
    }
    
    FILE* dst;
    dst = fopen(argv[2], "w");
    if(dst == NULL)
    {
        perror(argv[2]);
        return 3;
    }

    char toRead[BUF_SIZE];
    
    /* while(!feof(src))
    {
        size_t temp = fread(toRead, BUF_SIZE, 1, src);
        // fread(toRead, BUF_SIZE, 1, src);
        printf("%zu - %s\n", temp, toRead);
        fwrite(toRead, BUF_SIZE, 1, dst);
    } */ // It gets full of garbage... fread/fwrite and fwrite is most commonly used to read/write binary data.

    while(fgets(toRead, BUF_SIZE, src) != NULL)
    {
        fputs(toRead, dst);
    }

    fclose(src);
    fclose(dst);
    return 0;
}