/****************************************************************************
Title: Task
Author: Aviv Illoz
Description: Task interface header file
*****************************************************************************/

#include <stdio.h>	/* printf */
#include "task.h"	/* api */

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

/*****************************************************************************/

int main(void)
{
	size_t i = 0;
	int params = 40;
	ilrd_uid_t curr_uid;
	task_t *task_array[5];

	task_array[0] = TaskCreate(0, PrintIntParam, &params, 2);
	task_array[1] = TaskCreate(1, AddTen, &params, 0);
	task_array[2] = TaskCreate(3, SubtractTen, &params, 0);
	task_array[3] = TaskCreate(5, MultiplyByTen, &params, 0);
	task_array[4] = TaskCreate(7, DivideByTen, &params, 0);

	for (; i < 5; ++i)
	{
		curr_uid = TaskGetUid(task_array[i]);
		printf("%ld %ld %ld\n", UIDGetTime(curr_uid), 
					UIDGetPid(curr_uid), 
					UIDGetCounter(curr_uid));
	}

	printf("Execution time (before updated): %lu\n", TaskGetTime(task_array[0]));
	TaskUpdateTime(task_array[0]);
	printf("Execution time (after updated): %lu\n", TaskGetTime(task_array[0]));
	TaskUpdateTime(task_array[0]);
	printf("Execution time (after updated): %lu\n", TaskGetTime(task_array[0]));

	TaskExecute(task_array[0]);
	TaskExecute(task_array[1]);
	TaskExecute(task_array[0]);
	TaskExecute(task_array[2]);
	TaskExecute(task_array[0]);
	TaskExecute(task_array[3]);
	TaskExecute(task_array[0]);
	TaskExecute(task_array[4]);
	TaskExecute(task_array[0]);

	for (i = 0; i < 5; ++i)
	{
		TaskDestroy(task_array[i]);
	}

	return 0;
}
