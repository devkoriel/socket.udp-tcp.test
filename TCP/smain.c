#include <stdio.h>	// printf
#include <stdlib.h>	// exit
#include "server.h"	// serverOpen

int main(int argc, char **argv)
{
	// clear screen.
	system("clear");

	// check whether or not the execution command is valid.
	if (2 != argc)
	{
		printf("Usage: %s <port>\n", *argv);
		exit(1);
	}
	
	serverOpen(*(argv+1));

	return 0;
}
