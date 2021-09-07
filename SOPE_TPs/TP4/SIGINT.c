#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

void sigint_handler(int signo)
{
	printf("I can't be CRTL-C'ed :)\n");
	sleep(5);
}

int main(void)
{
	signal(SIGINT, sigint_handler);
	printf("I'm going to work very hard !\n");
	while(true);
//		printf("Working...\n");

	return 0;
}
