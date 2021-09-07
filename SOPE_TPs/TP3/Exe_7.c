#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])                                                                                                                                 
{
    char prog[20];
    sprintf(prog,"%s.c",argv[1]); // Program to execute...
    execlp("gcc","gcc",prog,"-Wall","-o",argv[1],NULL); // Looks for gcc in $PATH
    
    // It only executes if no "gcc" is found. If we put execlp("gccc","gcc",prog,"-Wall","-o",argv[1],NULL); it will not be executed, hence "Error" will appear.
    printf("Error!\n");
    exit(1);
} 