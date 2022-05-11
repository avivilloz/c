/****************************************************************************
Title: Scheduler Creator
Author: Aviv Illoz
Description: Scheduler Creator Interface
*****************************************************************************/

#ifndef __SCHEDULER_CREATOR_H__
#define __SCHEDULER_CREATOR_H__

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

#endif /*__SCHEDULER_CREATOR_H__*/
