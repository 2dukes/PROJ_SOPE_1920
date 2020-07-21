/*

Create ENV.Variable -> export NAME=VALUE

*Example*
export USER_NAME=RuiPinto

echo $USER_NAME -> To verify it.

Delete ENV.Variable -> unset USER_NAME

List all ENV.Variables -> set

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[])
{
    char pathVar[] = "USER_NAME";
    printf("Username: %s\n", getenv(pathVar));
    
    return 0;
}