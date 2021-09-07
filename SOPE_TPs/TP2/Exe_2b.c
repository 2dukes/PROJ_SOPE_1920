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
    if(argc != 3)
    {
        printf("Usage: %s <source> <destination>", argv[0]);
        return 1;
    }
    
    int src = open(argv[1], O_RDONLY);
    if(src == ERROR)
    {
        perror(argv[1]);
        return 2;
    }
    
    int dst = open(argv[2], O_WRONLY | O_CREAT , 0622);
    if(dst == ERROR)
    {
        perror(argv[2]);
        return 3;
    }

    char toRead[BUF_SIZE];
    int nr, nw;
    while((nr = read(src, toRead, BUF_SIZE)) > 0)
    {
        if((nw = write(dst, toRead, nr)) <= 0 || nw != nr)
        {
            perror(argv[2]);
            close(src);
            close(dst);
            return 4;
        }    
    } 

    close(src);
    close(dst);
    return 0;
}