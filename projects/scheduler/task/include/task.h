/****************************************************************************
Title: Task - Infinity Labs R&D 
Group: Ol91
Description: Task interface header file
*****************************************************************************/

#ifndef __TASK_INFITY_OL_91__
#define __TASK_INFITY_OL_91__ 
#include "uid.h"	/* API for UID */

typedef struct task task_t;

/******************************************************************************
* Description: create a new task with given arguments and a UID
* Input: action, params, frequency, time
* Output: UID of the new task created
* Error: returns BAD UID if it fails
******************/
task_t *TaskCreate(
		time_t init_execution_time,
		int (*action)(void *params),
		void *params, 
		unsigned long frequency
);

/******************************************************************************
* Description: destroy a given task
* Input: task *
* Output: none
* Error: - 
******************/
void TaskDestroy(task_t *task);

/******************************************************************************
* Description: get UID of the task
* Input: pointer to the task
* Output: UID
* Error: -
*****************/
ilrd_uid_t TaskGetUid(const task_t *task);

/******************************************************************************
* Description: execute a task
* Input: pointer to the task
* Output: the output of the action function, 0 on success, othervalues if not
* Error: -
***************/
int TaskExecute(const task_t *task);

/******************************************************************************
* Description: get the execution time of a task
* Input: pointer to the task
* Output: the next execution time of the task 
* Error: -
**************/
time_t TaskGetTime(const task_t *task);

/******************************************************************************
* Description: update the execution time of a task (push to the next execution time)
* Input: pointer to the task
* Output: -
* Error: -
**************/
void TaskUpdateTime(task_t *task);

/******************************************************************************
* Description: set the execution time of a task to a specific time
* Input: pointer to the task and the new time
* Output: -
* Error: -
**************/

void TaskSetTime(task_t *task, time_t time_to_set);

#endif /*__TASK_INFITY_OL_91*/









