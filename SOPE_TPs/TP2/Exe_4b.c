#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define NAME_SIZE 50

struct studentData
{
    char name[NAME_SIZE];
    int grade;
};

int main(int argc, char* argv[])
{
    struct studentData student;
    int n;

    write(STDOUT_FILENO, "Number of Students: ", 20);
    scanf("%d", &n);
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0644);

    // printf("%d - %s", errno, strerror(errno));

    for(int i = 1; i <= n; i++)
    {
        write(STDOUT_FILENO, "Name: ", 6);
        fgets(student.name , NAME_SIZE, stdin); // Read the \n from scanf...
        fgets(student.name , NAME_SIZE, stdin);

        write(STDOUT_FILENO, "Grade: ", 6);
        scanf("%d", &student.grade);

        write(fd, &student, sizeof(student));
        /*read(fd, &student, sizeof(student));
        printf("Name: %s | Grade: %d\n", student.name, student.grade);*/
    }

    close(fd);


}