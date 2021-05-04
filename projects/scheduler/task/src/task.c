/****************************************************************************
Title: Task
Author: Aviv Illoz
Description: Task interface header file
*****************************************************************************/

#include <stdlib.h>	/* malloc */
#include <assert.h>	/* assert */

#include "task.h"	/* api */
#include "uid.h"	/* API for UID */

struct task
{
	ilrd_uid_t uid;
	time_t execution_time;
	unsigned long frequency;
	int (*action)(void *params);
	void *params;
};

/******************************************************************************/

task_t *TaskCreate(
		time_t init_execution_time,
		int (*action)(void *params),
		void *params, 
		unsigned long frequency
)
{
	task_t *new_task = NULL;

	assert(NULL != action);
	
	new_task = malloc(sizeof(task_t));
	if (NULL == new_task)
	{
		free(new_task);
		return NULL;
	}

	new_task->action = action;
	new_task->params = params;
	new_task->uid = UIDCreate();
	new_task->execution_time = init_execution_time;
	new_task->frequency = frequency;

	return new_task;
}

/******************************************************************************/

void TaskDestroy(task_t *task)
{
	assert(NULL != task);

	free(task);
	task = NULL;	
}

/******************************************************************************/

ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(NULL != task);

	return task->uid;
}

/******************************************************************************/

int TaskExecute(const task_t *task)
{
	assert(NULL != task);

	return task->action(task->params);
}

/******************************************************************************/

time_t TaskGetTime(const task_t *task)
{
	assert(NULL != task);

	return task->execution_time;
}

/******************************************************************************/

void TaskUpdateTime(task_t *task)
{
	assert(NULL != task);

	task->execution_time += (time_t)task->frequency;
}

/******************************************************************************/

void TaskSetTime(task_t *task, time_t time_to_set)
{
	assert(NULL != task);

	task->execution_time = time_to_set;
}
