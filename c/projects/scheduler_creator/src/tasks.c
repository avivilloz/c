/****************************************************************************
Title: Scheduler Creator
Author: Aviv Illoz
Description: Scheduler Creator
*****************************************************************************/

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* system */
#include <time.h>

#include "tasks.h"		/* api */
#include "scheduler_creator.h"	/* api */

/*****************************************************************************/

void PrintTasks(void)
{
	size_t i = 0;
	printf("\nTasks:\n");
	for(; i < TASK_ARRAY_SIZE; ++i)
	{
		printf("%lu-%s  ", i + 1, task_array[i].name);
	}
	printf("%lu-Return\n", i + 1);
}

/*****************************************************************************/

action_temp_t TasksGetAction(action_temp_t action, unsigned int key)
{
	if (key >= TASK_ARRAY_SIZE)
	{
		return action;
	}

	action.action = task_array[key].action;

	return action;
}

/*****************************************************************************/

unsigned int TasksGetType(unsigned int key)
{
	if (key >= TASK_ARRAY_SIZE)
	{
		return -1;
	}

	return task_array[key].type;
}

/*****************************************************************************/

void InitializeTasksArray(void)
{
	task_array[0].type = 4;
	task_array[0].name = "Stop"; 
	task_array[0].action = Stop;

	task_array[1].type = 4;
	task_array[1].name = "CallSystem"; 
	task_array[1].action = CallSystem;

	task_array[2].type = 4;
	task_array[2].name = "CurrentTime"; 
	task_array[2].action = CurrTime;
}

/********************************** TASKS ************************************/

enum repeat {ONCE = -1, FOREVER};

int Stop(void *params)
{
	printf("%s", (char *)params);

	SchedulerStop(SchedStructToScheduler(curr_sched_struct));
	
	return ONCE;
}

int CallSystem(void *params)
{
	system((char *)params);

	return ONCE;
}

int CurrTime(void *params)
{
	time_t t = time(NULL);

	printf("%s: %s", (char *)params, asctime(localtime(&t)));

	return FOREVER;
}
