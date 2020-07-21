#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define READ 0
#define WRITE 1 
#define MAXLINE 10

int main(void)
{
    int fd1[2], fd2[2];
    pid_t pid;
    pipe(fd1); // Parent -> Son
    pipe(fd2); // Son -> Parent

    pid = fork();
    if (pid > 0) // Parent
    {
        int a[2]; 
        char toRead1, toRead2[MAXLINE];
        char operation[4][15] = {"Sum: ", "Diff: ", "Product: ", "Division: "};
        float fRes;
        int iRes;
        printf("x y ? "); scanf("%d %d",&a[0],&a[1]);
        close(fd1[READ]);
        close(fd2[WRITE]);

        write(fd1[WRITE], a , 2 * sizeof(int));
        
        for (int i = 0; i <= 3; i++) {
            read(fd2[READ], &toRead1, 1); // Type
            read(fd2[READ], &toRead2, MAXLINE); // Result
            write(STDOUT_FILENO, operation[i], strlen(operation[i]));
            if(toRead1 == '0') { // Case Integer
                sscanf(toRead2, "%d", &iRes);
                printf("%d\n", iRes);
            }   
            else if(toRead1 == '1') { // Case Float
                sscanf(toRead2, "%f", &fRes);
                printf("%f\n", fRes);
            }
            else if(toRead1 == '2')  // Case Invalid
                printf("Invalid\n");

            printf("\n-----\n");
        }
        
        close(fd1[WRITE]);
        close(fd2[READ]);
    }
    else // Son
    {
        int b[2]; // Second Position is for type specifier (0 -> Integer | 1 -> Float | 2 -> Invalid) ; First Position is for the result
        close(fd1[WRITE]);
        close(fd2[READ]);

        read(fd1[READ], b, 2 * sizeof(int));
        float result;
        char toWrite[MAXLINE];

        //----- Sum
        result = b[0] + b[1];
        strcpy(toWrite, "0");
        write(fd2[WRITE], toWrite, 1);
        sprintf(toWrite, "%d", (int) result);
        write(fd2[WRITE], toWrite, MAXLINE);

        
        //----- Diff
        result = b[0] - b[1];
        strcpy(toWrite, "0");
        write(fd2[WRITE], toWrite, 1);
        sprintf(toWrite, "%d", (int) result);
        write(fd2[WRITE], toWrite, MAXLINE);

        
        //----- Product
        result = b[0] * b[1];
        strcpy(toWrite, "0");
        write(fd2[WRITE], toWrite, 1);
        sprintf(toWrite, "%d", (int) result);
        write(fd2[WRITE], toWrite, MAXLINE);

        
        //----- Division
        if(b[1] == 0) { // Case Invalid
            strcpy(toWrite, "2");
            write(fd2[WRITE], toWrite, 1);
        }    
        else {
            result = (float) b[0] / b[1];
            if((int) result - result == 0) { // Case integer
                strcpy(toWrite, "0");
                write(fd2[WRITE], toWrite, 1);
                sprintf(toWrite, "%d", (int) result);
            }    
            else {                          // Case Float
                strcpy(toWrite, "1");
                write(fd2[WRITE], toWrite, 1);
                sprintf(toWrite, "%f", result);
            }
        }
        write(fd2[WRITE], toWrite, MAXLINE);

        close(fd1[READ]);
        close(fd2[WRITE]);
    }
    return 0;
}