/*****************************************************************************
Title: Prog_ex2 Ping Pong - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: David
Description: Prog_ex2 Ping Pong API
******************************************************************************/

#define _POSIX_C_SOURCE 200809L /* sigaction */

#include <stdio.h>		/* printf */
#include <signal.h>		/* sigaction */
#include <unistd.h>		/* getppid */

enum {FAILURE = -1};

static void PingHandler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;

	write(1 , "ping->", 7);
	kill(info->si_pid, SIGUSR1);
}

int main(void)
{
	struct sigaction ping;

	ping.sa_sigaction = PingHandler;
	ping.sa_flags = SA_SIGINFO;
	sigemptyset(&ping.sa_mask);

	if (FAILURE == sigaction(SIGUSR1, &ping, NULL))
	{
		printf("failed to change disposition\n\n");
		return 1;
	}

	kill(getppid(), SIGUSR2);

	while (1)
	{}

	return 0;	
}
