#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>

#define BUF_SIZE 256
#define ERROR   -1

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <FILE>", argv[0]);
        return 1;
    }
    
    int src = open(argv[1], O_RDONLY);
    if(src == ERROR)
    {
        perror(argv[1]);
        return 2;
    } 

    char toRead[BUF_SIZE];
    int nr;
    while((nr = read(src, toRead, BUF_SIZE)) > 0)
        write(STDOUT_FILENO, toRead, nr);           

    close(src);
    return 0;
}