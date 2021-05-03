/****************************************************************************
Title: Scheduler Heap - Infinity Labs R&D 
Group: Ol91
Description: Scheduler Heap interface header file
*****************************************************************************/

#ifndef __SCHEDULER_INFITY_OL_91__
#define __SCHEDULER_INFITY_OL_91__

#include <time.h>   	/* time_t */
#include <stddef.h> 	/* size_t */
#include "uid.h"	/* api */	
#include "pq_heap.h"	/* api */

typedef struct scheduler scheduler_t;

/*****************************************************************************/
/*
Decription:	Create new scheduler.	
Input:		None
Output:		Pointer to the created scheduler, NULL if memory allocation failed		
Error:      	Memory allocation failure
Time complexity:	O(1)
*/
scheduler_t *SchedulerCreate(void);

/*****************************************************************************/
/*
Decription:	Destroy a scheduler.	
Input:		Pointer to a scheduler
Output:		None		
Error:	        None
Time complexity:	O(1)
*/
void SchedulerDestroy(scheduler_t *scheduler);

/*****************************************************************************/
/*
Decription:	Create a task and insert it in the scheduler.	
Input:		Pointer to a scheduler, arguments of the task to insert.
Output:		The UID of the created task if success, BAD_ID if insertion failed,
                or Task creation failed.
Error:	        Memory allocation failure on creation of task or on insertion 
Time complexity:	O(n)
*/
ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler,
                             int (*action)(void *params),
                             void *params,
                             time_t first_execution,
                             unsigned long frequency);

/*****************************************************************************/
/*
Decription:	Remove a task from the scheduler.	
Input:		Pointer to a scheduler, uid of the task to remove.
Output:		0 if the task to remove was in the scheduler,
                non zero if the task was not found
Error:	        Task was not in the scheduler
Time complexity:	O(n)
*/
int SchedulerCancel(scheduler_t *scheduler, ilrd_uid_t to_remove);

/*****************************************************************************/
/*
Decription:	Count the number of task in the scheduler.	
Input:		Pointer to a scheduler.
Output:		Number of elements in the scheduler
Error:	        None
Time complexity:	O(n)
*/
size_t SchedulerSize(const scheduler_t *scheduler);

/*****************************************************************************/
/*
Decription:	Check if the scheduler is empty.	
Input:		Pointer to a scheduler.
Output:		1 if the scheduler is empty,
                0 if the scheduler is not empty
Error:	        None
Time complexity:	O(1)
*/
int SchedulerIsEmpty(const scheduler_t *scheduler);

/*****************************************************************************/
/*
Decription:	Clear the scheduler from all its task.	
Input:		Pointer to a scheduler.
Output:		None
Error:	        None
Time complexity:	O(n)
*/
void SchedulerClear(scheduler_t *scheduler);

/*****************************************************************************/
/*
Decription:	When this function is called, stop the scheduler.	
Input:		Pointer to a scheduler.
Output:		None.
Error:	        None.
Time complexity:	O(1)
*/

void SchedulerStop(scheduler_t *scheduler);

/*****************************************************************************/
/*
Decription:	Run the scheduler.	
Input:		Pointer to a scheduler.
Output:		None.
Error:	        Scheduler has no stop task / is empty.
*/

int SchedulerRun(scheduler_t *scheduler);

#endif /*__SCHEDULER_INFITY_OL_91*/
