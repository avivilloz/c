/*****************************************************************************
Title: Ping Pong - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: David
Description: Ping Pong API
******************************************************************************/

#define _POSIX_C_SOURCE 200809L /* sigaction */

#include <stdio.h>		/* printf */
#include <signal.h>		/* sigaction */
#include <wait.h>		/* wait */
#include <unistd.h>		/* fork */

/********************************** TEST *************************************/

enum {TEST_PASS, TEST_FAIL};

static void Test(int func_test, char *func_name)
{
	if (TEST_FAIL == func_test)
	{
		printf("%s: \33[5;1;31mFAILURE\33[0m\n", func_name);
	}
	else
	{
		printf("%s: \33[5;1;32;1mSUCCESS\33[0m\n", func_name);
	}
}

/*****************************************************************************/

#define CHILD 0

enum {FAILURE = -1};

/************************ FUNCTION DECLARATIONS ******************************/

int PingPong(void);
static void PingPongHandler(int sig, siginfo_t *info, void *ucontext);

int PingPong2(void);
static void PongHandler(int sig, siginfo_t *info, void *ucontext);
static void ContinueHandler(int sig, siginfo_t *info, void *ucontext);

int PingPong3(void);
static void PingHandler(int sig, siginfo_t *info, void *ucontext);

/*****************************************************************************/

int main(void)
{
	Test(PingPong(), "Ping-Pong");
/*
	Test(PingPong2(), "Ping-Pong-2");
	Test(PingPong3(), "Ping-Pong-3");
*/

	return 0;
}

/****************************** EXERCISES ***********************************/

/*
int PingPong(void)
{
	pid_t pid = 0;
	struct sigaction pingpong;

	pingpong.sa_sigaction = PingPongHandler;
	pingpong.sa_flags = SA_SIGINFO;	
	sigemptyset(&pingpong.sa_mask);

	if (FAILURE == sigaction(SIGUSR1, &pingpong, NULL))
	{
		return TEST_FAIL;
	}
	
	if (FAILURE == sigaction(SIGUSR2, &pingpong, NULL))
	{
		return TEST_FAIL;
	}

	pid = fork();

	if (FAILURE == pid)
	{
		printf("failed to create child process\n\n");
		return TEST_FAIL;
	}
	
	if (CHILD != pid)
	{
		while (1)
		{
			if (ON == game_flag)
			{
				fflush(stdout);
				printf("ping->");
				game_flag = OFF;
				kill(pid, SIGUSR2);
			}
		}
	}
	else
	{
		while (1)
		{
			if (OFF == game_flag)
			{
				printf("<-pong\n");
				game_flag = ON;
				kill(getppid(), SIGUSR1);
			}
		}
	}

	return TEST_PASS;
}
*/


int PingPong(void)
{
	pid_t pid = 0;
	struct sigaction pingpong;

	pingpong.sa_sigaction = PingPongHandler;
	pingpong.sa_flags = SA_SIGINFO;	
	sigemptyset(&pingpong.sa_mask);

	if (FAILURE == sigaction(SIGUSR1, &pingpong, NULL))
	{
		return TEST_FAIL;
	}
	
	if (FAILURE == sigaction(SIGUSR2, &pingpong, NULL))
	{
		return TEST_FAIL;
	}

	pid = fork();

	if (FAILURE == pid)
	{
		printf("failed to create child process\n\n");
		return TEST_FAIL;
	}
	else if (CHILD != pid)
	{
		kill(pid, SIGUSR2);
	}

	while (1)
	{}

	return TEST_PASS;
}

/*
*/
int PingPong2(void)
{
	pid_t pid = 0;
	struct sigaction pong;
	struct sigaction continue_runnning;

	pong.sa_sigaction = PongHandler;
	pong.sa_flags = SA_SIGINFO;	
	sigemptyset(&pong.sa_mask);

	if (FAILURE == sigaction(SIGUSR1, &pong, NULL))
	{
		return TEST_FAIL;
	}

	continue_runnning.sa_sigaction = ContinueHandler;
	continue_runnning.sa_flags = SA_SIGINFO;
	sigemptyset(&continue_runnning.sa_mask);

	if (FAILURE == sigaction(SIGUSR2, &continue_runnning, NULL))
	{
		return TEST_FAIL;
	}	

	pid = fork();

	if (FAILURE == pid)
	{
		printf("failed to create child process\n\n");
		return TEST_FAIL;
	}
	else if (CHILD == pid)
	{
		char *args[] = {"bin/prog.out", NULL};
		execv(args[0], args);
	}

	pause();

	kill(pid, SIGUSR1);

	while (1)
	{}

	return TEST_PASS;
}

/*
*/
int PingPong3(void)
{
	struct sigaction ping;

	ping.sa_sigaction = PingHandler;
	ping.sa_flags = SA_SIGINFO;	
	sigemptyset(&ping.sa_mask);

	if (FAILURE == sigaction(SIGUSR1, &ping, NULL))
	{
		return TEST_FAIL;
	}
	
	while (1)
	{}

	return TEST_PASS;
}

/******************************* HANDLERS ************************************/

/*
enum {OFF, ON};

static int game_flag = ON;

static void PingPongHandler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;

	if (SIGUSR1 == sig)
	{
		game_flag = ON;
	}
	else if (SIGUSR2 == sig)
	{
		game_flag = OFF;
	}
}
*/

static void PingPongHandler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	
	if (SIGUSR2 == sig)
	{
		write(1 , "ping->", 7);
		kill(info->si_pid, SIGUSR1);
	}
	else if (SIGUSR1 == sig)
	{
		write(1 , "<-pong\n", 8);
		kill(info->si_pid, SIGUSR2);
	}
}

static void PongHandler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;
	
	write(1 , "<-pong\n", 8);
	kill(info->si_pid, SIGUSR1);
}

static void ContinueHandler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
}

static void PingHandler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;

	write(1 , "ping->\n", 8);
	kill(info->si_pid, SIGUSR1);
}

/*****************************************************************************/
