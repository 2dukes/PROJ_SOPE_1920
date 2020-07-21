#include <stdio.h>

int main() {
    //char line[100] = "Hello World!";
    //FILE* fpout = popen("/home/whitelizard/Desktop/TP5/pipeTest/sender", "w");
    //fputs(line, fpout); // Sends "Hello World to sender program (names are swapped)"
    //pclose(fpout);

    FILE* fpin = popen("/home/whitelizard/Desktop/TP5/pipeTest/sender", "r");
    char to_read[100];
    fgets(to_read, 100, fpin);
    printf("%s-\n", to_read);
    pclose(fpin);
    

    return 0;

}