#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define BUF_SIZE 256

int main()
{
    struct termios tms, old;
    tcgetattr(STDIN_FILENO, &old);

    tms = old;
    tms.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tms); // I_Buffer is flushed
    write(STDOUT_FILENO, "\nPassword? ", 11);

    // DEACTIVATE ALL THE ECHOS AND CHANGE TO RAW MODE IMMEDIATELLY

    char toRead[BUF_SIZE], ch, ast = '*';
    int index = 0;

    // ONLY USE DIRECT OS CALLS

    while(index < BUF_SIZE && read(STDIN_FILENO, &ch, 1) && ch != '\n')
    {
        toRead[index++] = ch;
        write(STDOUT_FILENO, &ast, 1);
    }

    toRead[index] = '\0'; // Usefull when doing printfs...
    tcsetattr(STDOUT_FILENO, TCSANOW, &old); // Reestablish previous state..

    write(STDOUT_FILENO, "\n\nPASSWORD: ", 12);
    write(STDOUT_FILENO, toRead, strlen(toRead));
    write(STDOUT_FILENO, "\n", 1);

    return 0;
}