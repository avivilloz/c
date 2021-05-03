/****************************************************************************
Title: UID - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Sofia
Description: UID
****************************************************************************/

#include <stdio.h>	/* printf */
#include <unistd.h>	/* sleep */
#include "uid.h"	/* api */

/****************************************************************************/

static unsigned long UIDGetCounter(ilrd_uid_t uid);
static unsigned long UIDGetPid(ilrd_uid_t uid);
static unsigned long UIDGetTime(ilrd_uid_t uid);
static void UIDPrint(ilrd_uid_t uid);

/****************************************************************************/

int main(void)
{
	ilrd_uid_t uid_array[200];
	size_t i = 0;

	for (; i < 200; ++i)
	{
		uid_array[i] = UIDCreate();
		UIDPrint(uid_array[i]);
	}

	printf("Are uid_array[0] and uid_array[1] the same? %d\n", 
		UIDIsSame(uid_array[0], uid_array[1]));

	return 0;
}

/****************************************************************************/

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

/****************************************************************************/
