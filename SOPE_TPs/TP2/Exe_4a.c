#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define NAME_SIZE 50

int main(int argc, char* argv[])
{
    char name[NAME_SIZE];
    int grade, n;

    write(STDOUT_FILENO, "Number of Students: ", 20);
    scanf("%d", &n);
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0644);

    // printf("%d - %s", errno, strerror(errno));

    for(int i = 1; i <= n; i++)
    {
        write(STDOUT_FILENO, "Name: ", 6);
        fgets(name , NAME_SIZE, stdin); // Read the \n from scanf...
        fgets(name , NAME_SIZE, stdin);

        write(STDOUT_FILENO, "Grade: ", 6);
        scanf("%d", &grade);

        write(fd, name, strlen(name) + 1);
        char num[12];
        sprintf(num, "%d\n", grade);
        write(fd, num, 12);
    }

    close(fd);


}