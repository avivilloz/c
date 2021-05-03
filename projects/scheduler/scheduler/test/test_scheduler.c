/****************************************************************************
Title: Scheduler - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Sofia
Description: Scheduler interface header file
*****************************************************************************/

#include <stdio.h>	/* printf */
#include <unistd.h>	/* sleep */
#include "scheduler.h"	/* api */

/*****************************************************************************/

enum repeat {ONCE = -1, FOREVER};

static int PrintIntParam(void *params)
{
	static int counter = 5;

	printf("Param = %d\n", *(int *)params);

	--counter;

	return (0 == counter);
}

static int AddTen(void *params)
{
	*(int *)params += 10;

	sleep(2);	

	return ONCE;
}

static int SubtractTen(void *params)
{
	*(int *)params -= 10;

	return ONCE;
}

static int MultiplyByTen(void *params)
{
	*(int *)params *= 10;

	return ONCE;
}

static int DivideByTen(void *params)
{
	*(int *)params /= 10;

	return ONCE;
}

static int Stop(void *params)
{
	SchedulerStop((scheduler_t *)params);
	
	return ONCE;
}


/*****************************************************************************/

int main(void)
{
	int params = 40;
	ilrd_uid_t uid_array[6];
	scheduler_t *scheduler = SchedulerCreate();

	printf("****************** CREATED ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

	uid_array[0] = SchedulerAddTask(scheduler, PrintIntParam, &params, 0, 2);
	uid_array[1] = SchedulerAddTask(scheduler, AddTen, &params, 2, 0);
	uid_array[2] = SchedulerAddTask(scheduler, SubtractTen, &params, 4, 0);
	uid_array[3] = SchedulerAddTask(scheduler, MultiplyByTen, &params, 6, 0);
	uid_array[4] = SchedulerAddTask(scheduler, DivideByTen, &params, 8, 0);
	uid_array[5] = SchedulerAddTask(scheduler, DivideByTen, &params, 8, 0);

	printf("****************** INSERTED ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

	SchedulerCancel(scheduler, uid_array[5]);

	printf("****************** LAST CANCELED ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

	printf("****************** RUNNING FIRST TIME ***********************\n");

	printf("Run status: %d\n", SchedulerRun(scheduler));

/*****************************************************************************/

	uid_array[0] = SchedulerAddTask(scheduler, PrintIntParam, &params, 0, 2);
	uid_array[1] = SchedulerAddTask(scheduler, AddTen, &params, 2, 0);
	uid_array[2] = SchedulerAddTask(scheduler, SubtractTen, &params, 4, 0);
	uid_array[3] = SchedulerAddTask(scheduler, MultiplyByTen, &params, 6, 0);
	uid_array[4] = SchedulerAddTask(scheduler, DivideByTen, &params, 8, 0);

	printf("****************** INSERTED ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

	SchedulerClear(scheduler);

	printf("****************** CLEARED ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

/*****************************************************************************/

	uid_array[0] = SchedulerAddTask(scheduler, PrintIntParam, &params, 0, 2);
	uid_array[1] = SchedulerAddTask(scheduler, AddTen, &params, 2, 0);
	uid_array[2] = SchedulerAddTask(scheduler, SubtractTen, &params, 4, 0);
	uid_array[3] = SchedulerAddTask(scheduler, MultiplyByTen, &params, 6, 0);
	uid_array[4] = SchedulerAddTask(scheduler, DivideByTen, &params, 8, 0);
	uid_array[5] = SchedulerAddTask(scheduler, Stop, scheduler, 4, 0);

	printf("****************** INSERTED WITH STOP ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));
 
	printf("****************** RUNNING AGAIN WITH STOP ***********************\n");

	printf("Run status: %d\n", SchedulerRun(scheduler));

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

/*****************************************************************************/
	
	printf("****************** DESTROYING ***********************\n");

	SchedulerDestroy(scheduler);

	return 0;
}
