/*****************************************************************************
Title: Prog_ex3 Ping Pong
Author: Aviv Illoz
Description: Prog_ex3 Ping Pong API
******************************************************************************/

#define _POSIX_C_SOURCE 200809L /* sigaction */

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* atoi */
#include <signal.h>		/* sigaction */
#include <unistd.h>		/* getppid */

enum {FAILURE = -1};

static void PongHandler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;
	
	write(1 , "<-pong\n", 8);
	kill(info->si_pid, SIGUSR1);
}

int main(int argc, char *argv[])
{
	struct sigaction pong;

	pong.sa_sigaction = PongHandler;
	pong.sa_flags = SA_SIGINFO;
	sigemptyset(&pong.sa_mask);

	if (FAILURE == sigaction(SIGUSR1, &pong, NULL))
	{
		printf("failed to change disposition\n\n");
		return 1;
	}

	kill((pid_t)atoi(argv[argc - 1]), SIGUSR1);

	while (1)
	{}

	return 0;	
}
