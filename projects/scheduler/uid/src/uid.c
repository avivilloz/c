/****************************************************************************
Title: UID - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Sofia
Description: UID
****************************************************************************/

#include <stdio.h>	/* printf */
#include <time.h> 	/* time_t */
#include <unistd.h> /* pid_t */

#include "uid.h"	/* api */

/*****************************************************************************/

const ilrd_uid_t BAD_UID = {0,0,0};
static unsigned long count = 0;

/*****************************************************************************/

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t new_uid;
	time_t new_time = time(NULL);
	if (-1 == new_time)
	{
		return BAD_UID;
	}

	++count;

	new_uid.counter = count;	
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
