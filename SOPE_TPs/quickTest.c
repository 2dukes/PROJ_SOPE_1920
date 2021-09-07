#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char str[10];
	printf("%p | %p | %p \n", str, &str, &str[0]);
	printf("[1] - %p \n", &str[1]);

	char* auxStr = (char *) malloc(4 * sizeof(char));
	strcpy(auxStr, "abc");
        printf("%p | %p | %p \n", auxStr, &auxStr, &auxStr[0]);
	return 0;

}
