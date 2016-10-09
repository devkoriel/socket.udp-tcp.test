#include <stdio.h>	// printf
#include <stdlib.h>	// exit
#include "client.h"	// clientOpen

#ifndef boolean
#define boolean
typedef enum { false, true } bool;
#endif

bool askSending(const char* ip, const char* port);

int main(int argc, char **argv)
{
	// clear screen.
	system("clear");

	// check whether or not the execution command is valid.
	if (3 != argc)
	{
		printf("Usage: %s <IP> <port>\n", *argv);
		exit(1);
	}

	// ask whether or not sending file to server.
	if (askSending(*(argv+1), *(argv+2)))
		clientOpen(*(argv+1), *(argv+2));

	return 0;
}

bool askSending(const char* ip, const char* port)
{
	char c;

	// wait for starting to send file.
	printf("Send file to (%s:%s)? [Y/n] ", ip, port);

	do{
		c = getchar();
		while(getchar() != '\n'); 
		if (('n' == c) || ('N' == c))
			return false; 
	} while(('y' != c) && ('Y' != c));

	return true;
}
