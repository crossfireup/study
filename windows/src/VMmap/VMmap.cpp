#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void sig_break(int signo)
{
	fprintf(stderr, "get singal: %d\n", signo);
}

int main(int argc, char *argv[])
{
	signal(SIGBREAK, sig_break);
	sleep(1000);
	exit(0);
}
