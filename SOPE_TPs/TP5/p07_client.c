#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/types.h>

#define MAXLINE 128

struct toSend
{
    int num1;
    int num2;
    char op;
};


int main() {

    int towerController = open("/tmp/towerController", O_WRONLY);
    int clientManager = open("/tmp/clientFifo", O_RDONLY);

    int rBytes;    
    char result[MAXLINE];
    struct toSend infOp;

    do {
        scanf("%d %c %d", &infOp.num1, &infOp.op, &infOp.num2);
        write(towerController, &infOp, sizeof(infOp));
        rBytes = read(clientManager, result, MAXLINE);
        printf("Final Result: %s\n\n", result);

    } while(rBytes != 0);

    close(towerController);
    close(clientManager);

    return 0;
}    