/*****************************************************************************
Title: Shared
Author: Aviv Illoz
Description: Shared between client and watchdog
******************************************************************************/

#ifndef __PARTER_SHARED_H__
#define __PARTER_SHARED_H__

#include <stdio.h> /* perror */

/*****************************************************************************/

#define RETURN_IF_BAD(is_good, error_msg) \
	if (0 == is_good) \
	{ \
		perror(error_msg); \
		return 1; \
	}

/*****************************************************************************/

int SetGlobals(int argc, char *argv[], char *curr_process);

int GetPartner(void);

int PrepareSH(void (*signal_handler)(int, siginfo_t *, void *));

int OpenSems(int own_sem);

int CreateThreads(void);

int Scheduler(void);

void ResetCounter(void);

/* only used by client */
int DestroyPartnership(void);

/* only used by watchdog */
void WatchdogAutoDestroy(void);

/*****************************************************************************/

#endif /* __PARTER_SHARED_H__ */
