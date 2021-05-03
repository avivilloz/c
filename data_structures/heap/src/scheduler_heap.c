/****************************************************************************
Title: Scheduler Heap - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Igor
Description: Scheduler Heap interface header file
*****************************************************************************/

#include <stdlib.h>		/* malloc */
#include <assert.h>		/* assert */
#include <unistd.h>		/* sleep */

#include "scheduler_heap.h"	/* api */
#include "task.h"		/* api */

/******************************************************************************/

struct scheduler
{
	pq_t *scheduler;
	int is_running;
	task_t *curr_task;
};
	
/******************************************************************************/

enum status {SUCCESS, FAIL};

/***************************** STATIC FUNCTIONS *******************************/

static int SchedulerPriorityCmp(const void *exec1, const void *exec2);

/**************************/

static int IsEmptyNoExceptions(scheduler_t *scheduler);

/**************************/

static int SchedulerUidIsMatch(const void *uid1, const void *uid2);

/**************************/

static int SchedulerReschedule(int reschedule, scheduler_t *scheduler);
static void SchedulerReset(
	scheduler_t *scheduler, 
	time_t curr_time, 
	time_t start_time
);

/******************************** FUNCTIONS ***********************************/

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *new_scheduler = malloc(sizeof(scheduler_t));
	if (NULL == new_scheduler)
	{
		return NULL;
	}

	new_scheduler->scheduler = PQCreate(SchedulerPriorityCmp);
	if (NULL == new_scheduler->scheduler)
	{
		free(new_scheduler);
		new_scheduler = NULL;
		return NULL;
	}

	new_scheduler->is_running = 0;
	new_scheduler->curr_task = NULL;

	return new_scheduler;	
}

static int SchedulerPriorityCmp(const void *exec1, const void *exec2)
{
	return (TaskGetTime((task_t *)exec1) - TaskGetTime((task_t *)exec2));
}

/******************************************************************************/

void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	while (!IsEmptyNoExceptions(scheduler))
	{
		TaskDestroy((task_t *)PQDequeue(scheduler->scheduler));
	}
		
	PQDestroy(scheduler->scheduler);
	
	free(scheduler);
	scheduler = NULL;
}

static int IsEmptyNoExceptions(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
		
	return PQIsEmpty(scheduler->scheduler);
}

/******************************************************************************/

ilrd_uid_t SchedulerAddTask(
	scheduler_t *scheduler, 
	int (*action)(void *params),
	void *params, 
	time_t first_execution,
	unsigned long frequency
)
{
	task_t *new_task = NULL;

	assert(NULL != scheduler && NULL != action);

	new_task = TaskCreate(first_execution, action, params, frequency);
	if (NULL == new_task)
	{
		return BAD_UID;
	}

	if (FAIL == PQEnqueue(scheduler->scheduler, new_task))
	{
		free(new_task);
		new_task = NULL;
		return BAD_UID;
	}

	return TaskGetUid(new_task);
}

/******************************************************************************/

int SchedulerCancel(scheduler_t *scheduler, ilrd_uid_t to_remove)
{
	int check = 0;	
	void *data = NULL;

	assert(NULL != scheduler);	

	/* if task tries to remove itself */
	if (scheduler->is_running 
		&& UIDIsSame(TaskGetUid(scheduler->curr_task), to_remove))
	{
		free(scheduler->curr_task);
		scheduler->curr_task = NULL;	
	
		return check;
	}
	
	data = PQErase(scheduler->scheduler, SchedulerUidIsMatch, &to_remove);

	if (NULL == data)
	{
		check = 1;
	}

	TaskDestroy((task_t *)data);

	return check;	
}

static int SchedulerUidIsMatch(const void *uid1, const void *uid2)
{
	return UIDIsSame(*(ilrd_uid_t *)uid1, *(ilrd_uid_t *)uid2);
}

/******************************************************************************/

size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);

	return PQSize(scheduler->scheduler) + scheduler->is_running;
}

/******************************************************************************/

int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);

	return (PQIsEmpty(scheduler->scheduler) && NULL == scheduler->curr_task);
}

/******************************************************************************/

void SchedulerClear(scheduler_t *scheduler)
{
	assert(NULL != scheduler);

	while (!SchedulerIsEmpty(scheduler))
	{
		TaskDestroy((task_t *)PQDequeue(scheduler->scheduler));
	}

	/* if task tries to clear scheduler */
	if (scheduler->is_running)
	{
		free(scheduler->curr_task);
		scheduler->curr_task = NULL;
	}
}

/******************************************************************************/

int SchedulerRun(scheduler_t *scheduler)
{
	time_t start_time = time(NULL);
	time_t curr_time = 0;
	time_t curr_task_exec = 0;
	int check = 0;

	assert(NULL != scheduler);

	scheduler->is_running = 1;

	while (scheduler->is_running && !SchedulerIsEmpty(scheduler))
	{
		curr_time = time(NULL);
		scheduler->curr_task = (task_t *)PQDequeue(scheduler->scheduler);
		curr_task_exec = TaskGetTime(scheduler->curr_task) + start_time;

		/* if a task took time and surpassed the curr_task_exec */
		if (curr_time > curr_task_exec)
		{
			TaskSetTime(scheduler->curr_task, curr_time - start_time);
		}

		if (curr_time < curr_task_exec)
		{
			sleep(curr_task_exec - curr_time);
		}

		check = SchedulerReschedule(TaskExecute(scheduler->curr_task), scheduler);
		if (FAIL == check)
		{
			return -1;
		}
	}

	if (!scheduler->is_running)
	{
		SchedulerReset(scheduler, curr_time, start_time);
	}

	scheduler->is_running = 0;

	return !SchedulerIsEmpty(scheduler);
}

static int SchedulerReschedule(int reschedule, scheduler_t *scheduler)
{
	int check = 0;

	if (SUCCESS == reschedule)
	{
		TaskUpdateTime(scheduler->curr_task);
		check = PQEnqueue(scheduler->scheduler, scheduler->curr_task);
		if (FAIL == check)
		{
			return 1;
		}
		return 0;
	}

	free(scheduler->curr_task);
	scheduler->curr_task = NULL;

	return 0;
}

static void SchedulerReset(
	scheduler_t *scheduler, 
	time_t curr_time, 
	time_t start_time
)
{
	scheduler_t *buffer = NULL;
	task_t *temp = NULL;
	time_t time_to_set = 0;

	buffer = SchedulerCreate();
	if (NULL == buffer)
	{
		return;
	}

	while (!SchedulerIsEmpty(scheduler))
	{
		temp = (task_t *)PQDequeue(scheduler->scheduler);
		time_to_set = TaskGetTime(temp) - (curr_time - start_time);
		TaskSetTime(temp, time_to_set);
		PQEnqueue(buffer->scheduler, temp);
	}
	
	while (!SchedulerIsEmpty(buffer))
	{
		temp = (task_t *)PQDequeue(buffer->scheduler);
		PQEnqueue(scheduler->scheduler, temp);
	}
		
	SchedulerDestroy(buffer);
}

/******************************************************************************/

void SchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);

	scheduler->is_running = 0;
}

/******************************************************************************/
