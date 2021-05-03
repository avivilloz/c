/****************************************************************************
Title: Scheduler Logger
Author: Aviv
Description: Scheduler Logger interface
*****************************************************************************/

#ifndef _SCHEDULER_CREATOR_
#define _SCHEDULER_CREATOR_
#include "scheduler.h"		/* api */

/*****************************************************************************/

typedef struct sched_struct scheduler_struct_t;
scheduler_struct_t *curr_sched_struct;

typedef struct task_struct task_struct_t;

typedef struct types types_t;

/*****************************************************************************/

int CreateScheduler(void);

/*****************************************************************************/

int DestroyScheduler(void);

/*****************************************************************************/

int Exit(void);

/*****************************************************************************/

int OpenScheduler(void);

/*****************************************************************************/

int AddTask(void);

/*****************************************************************************/

int CancelTaskLogger(void);

/*****************************************************************************/

int RunScheduler(void);

/*****************************************************************************/

int ClearScheduler(void);

/*****************************************************************************/

int PrintTasksUidList(void);

/*****************************************************************************/

scheduler_t *SchedStructToScheduler(scheduler_struct_t *sched_struct);

/*****************************************************************************/

#endif /*_SCHEDULER_CREATOR_*/
