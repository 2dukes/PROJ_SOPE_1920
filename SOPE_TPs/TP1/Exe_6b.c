// PROGRAMA p6a.c 
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUF_LENGTH 256 
#define MAX 112

int main(void) 
{   
    FILE *src, *dst;   
    char buf[BUF_LENGTH];   
    
    
    if ( ( src = fopen( "infile.txt", "r" ) ) == NULL ) 
    {    
        perror("Infile.txt 1 :: ");
        printf("ERRONO: %d\n", errno); // strerror(errno) -> To get the error description...
        printf("Infile.txt 2 ::: %s\n", strerror(2)); // #define ENOENT   2 /* No such file or directory */
        exit(1);   
    }      
    if ( ( dst = fopen( "outfile.txt", "w" ) ) == NULL )   
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

/*

Resposta 6 b) -> O programa sai com exit(1), pois não existe nenhum ficheiro chamado infile.txt (nem outfile.txt).
echo $? -> Para ver a terminação do programa (1).

Resposta 6 f) -> Criou-se o infile.txt e verificou-se que outfile.txt tem o conteúdo correto. O errno foi 0, ou seja SUCESSO.
*/
