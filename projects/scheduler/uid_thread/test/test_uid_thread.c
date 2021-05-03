/****************************************************************************
Title: UID (thread-safe) - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Nour
Description: UID
****************************************************************************/

#include <stdio.h>		/* printf */
#include <stdlib.h> 	/* malloc, free */
#include <unistd.h>		/* sleep */
#include <pthread.h>	/* thread functions */

#include "uid_thread.h"		/* api */

/*****************************************************************************/

static unsigned long UIDGetCounter(ilrd_uid_t uid);
static unsigned long UIDGetPid(ilrd_uid_t uid);
static unsigned long UIDGetTime(ilrd_uid_t uid);
static void UIDPrint(ilrd_uid_t uid);
static int IsBadUid(ilrd_uid_t uid);
static void *GetUid(void *param);

/******************************* Helper **************************************/

static void ExitIfBad(int is_good, int exit_value, const char *error_msg)
{
	if (!is_good)
	{
		perror(error_msg);
		exit(exit_value);
	}
}

/*****************************************************************************/

#define NUM_OF_THREADS 20

/*****************************************************************************/

int main(void)
{
	void *uid_array[NUM_OF_THREADS];
	pthread_t threads[NUM_OF_THREADS];
	size_t i = 0;

	for (; i < NUM_OF_THREADS; ++i)
	{
		ExitIfBad(0 == pthread_create(&threads[i], NULL, GetUid, NULL), 1, "Error");
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(threads[i], &uid_array[i]);
		UIDPrint(*(ilrd_uid_t *)uid_array[i]);
		if (i > 0)
		{
			printf("Are uid_array[%lu] and uid_array[%lu] the same? %d\n", i, i - 1,
			UIDIsSame(*(ilrd_uid_t *)uid_array[i], *(ilrd_uid_t *)uid_array[i - 1]));
		}
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		free(uid_array[i]);
		uid_array[i] = NULL;
	}

	return 0;
}

/*****************************************************************************/

static unsigned long UIDGetCounter(ilrd_uid_t uid)
{
	return uid.counter; 
}

static unsigned long UIDGetPid(ilrd_uid_t uid)
{
	return (unsigned long)uid.pid;
}

static unsigned long UIDGetTime(ilrd_uid_t uid)
{
	return (unsigned long)uid.time;
}

static void UIDPrint(ilrd_uid_t uid)
{
	printf("%ld %ld %ld\n", UIDGetTime(uid), UIDGetPid(uid), UIDGetCounter(uid));
}

static int IsBadUid(ilrd_uid_t uid)
{
	return 0 == UIDGetTime(uid) && 0 == UIDGetPid(uid) && 0 == UIDGetCounter(uid); 
}

static void *GetUid(void *param)
{
	ilrd_uid_t *uid = (ilrd_uid_t *)malloc(sizeof(ilrd_uid_t));
	ExitIfBad(NULL != uid, 2, "Error");

	*uid = UIDCreate();
	ExitIfBad(0 == IsBadUid(*uid), 3, "Error");

	(void)param;

	return uid;
}

/*****************************************************************************/
