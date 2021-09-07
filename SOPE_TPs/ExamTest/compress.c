#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char toRead[100];
    printf("%ld\n", sizeof(toRead));
    printf("%ld\n", strlen(toRead));
    if(fgets(toRead, sizeof(toRead), stdin) == NULL)
        printf("CTRL+D\n");
    
    printf("%s\n", toRead);

    return 0;
}