/****************************************************************************
Title: UID (thread-safe)
Author: Aviv Illoz
Description: UID (thread-safe)
****************************************************************************/

#include <stdio.h>		/* printf */
#include <errno.h>		/* perror */
#include <time.h> 		/* time_t */
#include <unistd.h> 	/* pid_t */
#include <pthread.h>	/* mutex */

#include "uid_thread.h"		/* api */

/*****************************************************************************/

const ilrd_uid_t BAD_UID = {0, 0, 0};
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static unsigned long counter = 0;

/*****************************************************************************/

ilrd_uid_t UIDCreate(void)
{
	time_t new_time = time(NULL); /* time cannot fail if NULL is specified */
	ilrd_uid_t new_uid;

	/* lock */
	if (0 != pthread_mutex_lock(&g_lock))
	{
		perror("pthread_mutex_lock error");
		return BAD_UID;
	}

	new_uid.counter = counter;	
	++counter;

	/* unlock */
	if (0 != pthread_mutex_unlock(&g_lock))
	{
		perror("pthread_mutex_unlock error");
		return BAD_UID;
	}

	new_uid.time = new_time;
	new_uid.pid = getpid();	
	
	return new_uid;
}

/*****************************************************************************/
           
int UIDIsSame(ilrd_uid_t lhs, ilrd_uid_t rhs)
{
	return (lhs.time == rhs.time && lhs.pid == rhs.pid && 
			lhs.counter == rhs.counter);
}

/*****************************************************************************/
