#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define BUF_SIZE 256
#define ERROR   -1

int main(int argc, char *argv[])
{
    if(argc != 2 && argc != 3)
    {
        printf("Usage: %s <FILE> [<DEST>]", argv[0]);
        return 1;
    }
    
    int src = open(argv[1], O_RDONLY);
    if(src == ERROR)
    {
        perror(argv[1]);
        return 2;
    } 
    
    int new, dst;
    if(argc == 3)
    {    
        new = dup(STDOUT_FILENO);
        dst = open(argv[2], O_WRONLY | O_CREAT, 0644);

        if(dst == ERROR)
        {
            perror(argv[2]);
            return 2;
        } 
        dup2(dst, STDOUT_FILENO);
    }

    char toRead[BUF_SIZE];
    int nr, nw;
    while((nr = read(src, toRead, BUF_SIZE)) > 0)
    {
        if((nw = write(STDOUT_FILENO, toRead, nr)) <= 0 || nr != nw)
        {
            perror(argv[2]);
            close(src);
            if(argc == 3)
                close(dst);
            return 3;
        }
        
    }

    if(argc == 3)
    {
        dup2(new, STDOUT_FILENO);
        close(dst);
    }

    close(src);
    
    return 0;
}