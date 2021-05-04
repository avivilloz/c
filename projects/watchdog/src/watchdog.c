/*****************************************************************************
Title: Watchdog
Author: Aviv Illoz
Description: Watchdog program for ressucitating client
******************************************************************************/

#define _POSIX_C_SOURCE 200809L /* sigaction */

#include <signal.h>             /* siginfo_t */

#include "shared.h"             /* shared with client */

/*****************************************************************************/

#define OWN_SEM 1

/*****************************************************************************/

static void WatchdogSH(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	
	if (SIGUSR1 == sig)
	{
		ResetCounter();
	}
	else
	{
		WatchdogAutoDestroy();
	}
}

/*****************************************************************************/

int main(int argc, char *argv[])
{
	/* set globals from partner_shared file */
	RETURN_IF_BAD((0 == SetGlobals(argc, argv, "WATCHDOG")), "GetArgs() - Error");

	/* get pid of partner */
	RETURN_IF_BAD((0 == GetPartner()), "CreatePartner() - Error");
	
	/* prepare signal handler to set counter to 0 everytime watchdog
	sends signal */
	RETURN_IF_BAD((0 == PrepareSH(WatchdogSH)), "PrepareSH() - Error");

	/* semaphore to allow scheduler to start, only after watchdog and client 
	are ready */
	RETURN_IF_BAD((0 == OpenSems(OWN_SEM)), "OpenSems() - Error");

	RETURN_IF_BAD((0 == Scheduler()), "Scheduler() - Error");

	return 0;
}

/*****************************************************************************/
