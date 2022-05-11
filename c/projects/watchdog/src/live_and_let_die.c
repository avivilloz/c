/*****************************************************************************
Title: Live and Let Die
Author: Aviv Illoz
Description: Live and Let Die API
******************************************************************************/

#define _POSIX_C_SOURCE 200809L /* sigaction */

#include <pthread.h>            /* mutex */
#include <signal.h>             /* siginfo_t */

#include "shared.h"             /* shared with watchdog */
#include "live_or_let_die.h"    /* api */

/*****************************************************************************/

#define OWN_SEM 0

/*****************************************************************************/

static int g_is_immortal = 0;

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

/*****************************************************************************/

static void ClientSH(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	
	if (SIGUSR1 == sig)
	{
		ResetCounter();
	}
	else
	{
		LetMeDie();
	}
}

/*****************************************************************************/

int KeepMeAlive(int argc, char *argv[])
{
	RETURN_IF_BAD((0 == pthread_mutex_lock(&g_lock)), "pthread_mutex_lock() - Error");

	if (g_is_immortal)
	{
		return 0;
	}

	g_is_immortal = 1;

	/* set globals from partner_shared file */
	RETURN_IF_BAD((0 == SetGlobals(argc, argv, "CLIENT")), "GetArgs() - Error");

	/* create watchdog or gets its pid if is parent */
	RETURN_IF_BAD((0 == GetPartner()), "CreatePartner() - Error");

	/* prepare signal handler to set counter to 0 everytime watchdog
	sends signal */
	RETURN_IF_BAD((0 == PrepareSH(ClientSH)), "PrepareSH() - Error");

	/* semaphore to allow scheduler to start, only after watchdog and client 
	are ready */
	RETURN_IF_BAD((0 == OpenSems(OWN_SEM)), "OpenSems() - Error");

	/* 1- thread for checking return value of threads and tasks, if any thread fails,
	this thread calls LetMeDie, in order to free every allocated memory
	and let the program finish naturally. 2- Scheduler */
	RETURN_IF_BAD((0 == CreateThreads()), "CreateThreads() - Error");

	RETURN_IF_BAD((0 == pthread_mutex_unlock(&g_lock)), "pthread_mutex_unlock() - Error");

	return 0;
}

/*****************************************************************************/

int LetMeDie(void)
{
	RETURN_IF_BAD((0 == pthread_mutex_lock(&g_lock)), "pthread_mutex_lock() - Error");

	if (!g_is_immortal)
	{
		return 0;
	}

	g_is_immortal = 0;


	RETURN_IF_BAD((0 == DestroyPartnership()), "DestroyPartnership() - Error");

	RETURN_IF_BAD((0 == pthread_mutex_unlock(&g_lock)), "pthread_mutex_unlock() - Error");

	return 0;
}

/*****************************************************************************/
