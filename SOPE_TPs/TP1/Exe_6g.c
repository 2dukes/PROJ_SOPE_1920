#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUF_LENGTH 256 
#define MAX 112

int main(int argc, char* argv[]) 
{   
    FILE *src, *dst;   
    char buf[BUF_LENGTH];   
    
    if(argc != 3) // Alínea h)
    {
        printf("usage: nome_do_executavel file1 file2\n");
        exit(0);
    }
    if ( ( src = fopen( argv[1], "r" ) ) == NULL ) 
    {    
        perror("Infile.txt 1 :: ");
        printf("ERRONO: %d\n", errno); // strerror(errno) -> To get the error description...
        printf("Infile.txt 2 ::: %s\n", strerror(errno)); // #define ENOENT   2 /* No such file or directory */
        exit(1);   
    }      
    if ( ( dst = fopen( argv[2], "w" ) ) == NULL )   
    {  
        perror("Outfile.txt : ");
        printf("ERRONO: %d\n", errno);
        exit(2);   
    }
    // fgets explanation -> https://www.geeksforgeeks.org/fgets-gets-c-language/
    // gets is used for reading strings in STDIN
    while( ( fgets( buf, MAX, src ) ) != NULL )       
        fputs( buf, dst ); 

    fclose( src );   
    fclose( dst );   
    perror("Ending :");
    printf("ERRONO: %d\n", errno);
    exit(0);  // zero é geralmente indicativo de "sucesso" 
}