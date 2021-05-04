/****************************************************************************
Title: Scheduler Creator
Author: Aviv Illoz
Description: Scheduler Creator
*****************************************************************************/

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc */
#include <assert.h>		/* assert */
#include "scheduler_creator.h"	/* api */
#include "slist.h"		/* api */
#include "queue.h"		/* api */
#include "dlist.h"		/* api */
#include "sorted_list.h"	/* api */
#include "pq.h"			/* api */
#include "task.h"		/* api */
#include "scheduler.h"		/* api */
#include "tasks.h"		/* api */
#include "menu.h"		/* api */

#define OP_ARRAY_SIZE 4
static op_t op_array[OP_ARRAY_SIZE];
#define SCHED_OP_ARRAY_SIZE 6
static op_t sched_op_array[SCHED_OP_ARRAY_SIZE];

/*****************************************************************************/

struct sched_struct
{
	unsigned int cmd;
	slist_iter_t from;
	slist_iter_t to;
	scheduler_t *scheduler;
	char name[20];
};

static dlist_t *scheduler_list = NULL;
static dlist_iter_t scheduler_list_iter;

/*****************************************************************************/

struct task_struct
{
	unsigned int cmd;
	int (*cmp)(unsigned int cmd, unsigned int key);
	task_t *task;
	ilrd_uid_t uid;
	void *params;
	unsigned int type;
	char *task_name;
};

static slist_t *tasks_uid_list = NULL;

/*****************************************************************************/

struct types
{
	int i;
	float f;
	char c;
	char str[50];
};

static queue_t *params_queue = NULL;

/*****************************************************************************/

static void InitializeSchedulerList(void);
static void InitializeTasksUid(void);
static void InitializeParamsQueue(void);
static void InitializeOpArray(void);
static void InitializeSchedOpArray(void);

/*****************************************************************************/

int main(void)
{
	InitializeTasksArray();
	InitializeSchedulerList();
	InitializeTasksUid();
	InitializeParamsQueue();
	InitializeOpArray();
	InitializeSchedOpArray();
	Logger(op_array, OP_ARRAY_SIZE);

	return 0;
}

/*****************************************************************************/

static void InitializeSchedulerList(void)
{
	scheduler_list = DListCreate();
	assert(NULL != scheduler_list);
}

static void InitializeTasksUid(void)
{
	tasks_uid_list = SListCreate();
	assert(NULL != tasks_uid_list);
}

static void InitializeParamsQueue(void)
{
	params_queue = QCreate();
	assert(NULL != params_queue);
}

/*****************************************************************************/

static int KeyCmp(unsigned int cmd, unsigned int key)
{
	return (cmd == key);
}

/*****************************************************************************/

static void InitializeOpArray(void)
{
	op_array[0].name = "Create";
	op_array[0].cmd = 1;
	op_array[0].cmp = KeyCmp;
	op_array[0].action = CreateScheduler;
	
	op_array[1].name = "Open";
	op_array[1].cmd = 2;
	op_array[1].cmp = KeyCmp;
	op_array[1].action = OpenScheduler;

	op_array[2].name = "Destroy";
	op_array[2].cmd = 3;
	op_array[2].cmp = KeyCmp;
	op_array[2].action = DestroyScheduler;

	op_array[3].name = "Exit";
	op_array[3].cmd = 4;
	op_array[3].cmp = KeyCmp;
	op_array[3].action = Exit;
}

/*****************************************************************************/

static void InitializeSchedOpArray(void)
{
	sched_op_array[0].name = "Run";
	sched_op_array[0].cmd = 1;
	sched_op_array[0].cmp = KeyCmp;
	sched_op_array[0].action = RunScheduler;

	sched_op_array[1].name = "Tasks";
	sched_op_array[1].cmd = 2;
	sched_op_array[1].cmp = KeyCmp;
	sched_op_array[1].action = PrintTasksUidList;

	sched_op_array[2].name = "AddTask";
	sched_op_array[2].cmd = 3;
	sched_op_array[2].cmp = KeyCmp;
	sched_op_array[2].action = AddTask;

	sched_op_array[3].name = "CancelTask";
	sched_op_array[3].cmd = 4;
	sched_op_array[3].cmp = KeyCmp;
	sched_op_array[3].action = CancelTaskLogger;

	sched_op_array[4].name = "Clear";
	sched_op_array[4].cmd = 5;
	sched_op_array[4].cmp = KeyCmp;
	sched_op_array[4].action = ClearScheduler;

	sched_op_array[5].name = "Return";
	sched_op_array[5].cmd = 6;
	sched_op_array[5].cmp = KeyCmp;
	sched_op_array[5].action = Return;
}

/******************************************************************************/

int CreateScheduler(void)
{
	scheduler_struct_t *new_sched_struct = malloc(sizeof(scheduler_struct_t));
	assert(NULL != new_sched_struct);

	DListPushBack(scheduler_list, new_sched_struct);

	printf("\nScheduler Name: ");
	scanf("%s", new_sched_struct->name);
	new_sched_struct->cmd = DListSize(scheduler_list);
	new_sched_struct->from = SListEnd(tasks_uid_list);
	new_sched_struct->to = SListEnd(tasks_uid_list);
	new_sched_struct->scheduler = SchedulerCreate();
	if (NULL == new_sched_struct->scheduler)
	{		
		printf("Fail to Create Scheduler\n");
		free(new_sched_struct);
		new_sched_struct = NULL;
		return CONTINUE;
	}

	printf("<%s> Created\n", new_sched_struct->name);

	return CONTINUE;
}

/*****************************************************************************/

/* for Destroy and Open */
static void DisplaySchedulerOptions(void)
{
	dlist_iter_t runner = DListBegin(scheduler_list);

	printf("\nChoose Scheduler\n");
	for (; !DListIsSameIterator(runner, DListEnd(scheduler_list))
						; runner = DListNext(runner))
	{
		printf("%u-<%s>  ", ((scheduler_struct_t *)DListGetData(runner))->cmd, ((scheduler_struct_t *)DListGetData(runner))->name);
	}
	printf("%lu-Return\n", DListSize(scheduler_list) + 1);
}

/* for Destroy and SchedulerLogger */
static int IsMatch(const void *lhs, const void *rhs)
{
	return (((scheduler_struct_t *)lhs)->cmd == *(unsigned int *)rhs);
}

/* for Destroy only */
static int ResetSchedulerCmds(void *data, void *param)
{
	(void)param;

	--((scheduler_struct_t *)data)->cmd; 

	return 0;
}

int DestroyScheduler(void)
{
	unsigned int key = 0;

	if (DListIsEmpty(scheduler_list))
	{
		printf("\nNo schedulers created\n");
		return CONTINUE;
	}

	DisplaySchedulerOptions();
	scanf("%u", &key);

	if (key < DListSize(scheduler_list) + 1)	
	{
		scheduler_list_iter = DListFind(DListBegin(scheduler_list)
						, DListEnd(scheduler_list)
						, IsMatch
						, &key);

		curr_sched_struct = (scheduler_struct_t *)DListGetData(scheduler_list_iter);

		ClearScheduler();

		SchedulerDestroy(curr_sched_struct->scheduler);
		printf("Destroyed\n");

		free(curr_sched_struct);
		curr_sched_struct = NULL;

		scheduler_list_iter = DListRemove(scheduler_list_iter);

		DListForEach(scheduler_list_iter, DListEnd(scheduler_list)
						, ResetSchedulerCmds, NULL);
	}
	
	return CONTINUE;
}

/*****************************************************************************/

int Exit(void)
{
	slist_iter_t runner1 = SListBegin(tasks_uid_list);
	dlist_iter_t runner2 = DListBegin(scheduler_list);

	while (!DListIsSameIterator(runner2, DListEnd(scheduler_list)))
	{
		SchedulerDestroy(((scheduler_struct_t *)DListGetData(runner2))->scheduler);
		runner2 = DListNext(runner2);
		free(DListPopFront(scheduler_list));		
	}
	DListDestroy(scheduler_list);
	/************************/
	for (; !SListIsSameIterator(runner1, SListEnd(tasks_uid_list))
		; runner1 = SListNext(runner1))
	{
		free(SListGetData(runner1));
	} 
	SListDestroy(tasks_uid_list);
	/************************/
	while (!QIsEmpty(params_queue))
	{
		free(QFront(params_queue));
		QDequeue(params_queue);
	}
	QDestroy(params_queue);
	/************************/
	printf("\nBye\n\n");

	return EXIT;
}

/*****************************************************************************/

/* after choosing the scheduler, this function opens the  logger of options */
static int SchedulerLogger(unsigned int key)
{
	if (key == DListSize(scheduler_list) + 1)
	{
		return EXIT;
	}

	scheduler_list_iter = DListFind(DListBegin(scheduler_list)
						, DListEnd(scheduler_list)
						, IsMatch
						, &key);

	curr_sched_struct = (scheduler_struct_t *)DListGetData(scheduler_list_iter);

	printf("\n********************* <%s>  Size: %lu *********************\n"
	, curr_sched_struct->name
	, SchedulerSize(curr_sched_struct->scheduler));
	
	return Logger(sched_op_array, SCHED_OP_ARRAY_SIZE);
}

/*****************************************************************************/

int OpenScheduler(void)
{
	unsigned int key = 0;
	int check = 0;

	if (DListIsEmpty(scheduler_list))
	{
		printf("\nNo schedulers created\n");
		return CONTINUE;
	}

	do {
		DisplaySchedulerOptions();
		scanf("%u", &key);

		check = SchedulerLogger(key);
	} while (EXIT != check);

	return CONTINUE;
}

/*****************************************************************************/

/* for SetTaskOfNewTaskUid */
static int UidIsMatch(const void *task, const void *uid_to_find)
{
	return UIDIsSame(TaskGetUid((task_t *)task), *(ilrd_uid_t *)uid_to_find);
}

/* for AllocateForNewTaskUid */
static void SetTaskOfNewTaskUid(task_struct_t *new_task_struct, ilrd_uid_t curr_uid)
{
	sorted_list_iter_t sched_runner, end;

	sched_runner = SortedListBegin(PQToSortedList(SchedulerToQueue(
					curr_sched_struct->scheduler)));
	end = SortedListEnd(PQToSortedList(SchedulerToQueue(
					curr_sched_struct->scheduler)));
	
	sched_runner = SortedListFindIf(sched_runner, end, UidIsMatch, &curr_uid);

	new_task_struct->task = (task_t *)SortedListGetData(sched_runner);
}

static void AllocateForNewTaskUid(unsigned int key, ilrd_uid_t curr_uid
					, void *params, unsigned int type)
{
	task_struct_t *new_task_struct = malloc(sizeof(task_struct_t));
	assert(NULL != new_task_struct);

	curr_sched_struct->to = 
		SListNext(SListInsert(curr_sched_struct->to, new_task_struct));

	new_task_struct->cmd = SListSize(tasks_uid_list);
	new_task_struct->cmp = KeyCmp;
	SetTaskOfNewTaskUid(new_task_struct, curr_uid);
	new_task_struct->uid = curr_uid;
	new_task_struct->params = params;
	new_task_struct->type = type;
	new_task_struct->task_name = task_array[key].name;
}

/*****************************************************************************/

static void *ChooseParameter(unsigned int type)
{
	void *params = NULL;
	char *runner = NULL;
	types_t *new_types_struct = malloc(sizeof(types_t));
	assert(NULL != new_types_struct);

	QEnqueue(params_queue, new_types_struct);

	new_types_struct->i = 0; 
	new_types_struct->f = 0;
	new_types_struct->c = '\0';

	switch (type)
	{
	case 1:
		printf("INT type: ");
		scanf("%d", &new_types_struct->i);
		params = &new_types_struct->i;
		return params;
	case 2:
		printf("FLOAT type: ");
		scanf("%f", &new_types_struct->f);
		params = &new_types_struct->f;
		return params;
	case 3:
		printf("CHAR type: ");
		scanf("%c", &new_types_struct->c);
		params = &new_types_struct->c;
		return params;
	case 4:
		printf("STRING type: ");
		getchar();
		fgets(new_types_struct->str, 50, stdin);
		for (runner = new_types_struct->str; '\n' != *runner; ++runner)
		{}
		*runner = '\0';
		params = new_types_struct->str;
		return params;
	default:
		return NULL;
	}
}

/*****************************************************************************/

int AddTask(void)
{
	unsigned int key = 0;
	unsigned int type = 0;
	void *params = NULL;
	unsigned long first_execution = 0;
	unsigned long frequency = 0;
	action_temp_t action;
	ilrd_uid_t curr_uid;

	/* function from tasks.h lib */
	PrintTasks();
	scanf("%u", &key);

	--key;

	if (TASK_ARRAY_SIZE == key)
	{
		return CONTINUE;
	}

	printf("\nParameter to send of ");
	type = task_array[key].type;
	params = ChooseParameter(type);
	assert(NULL != params);

	printf("First Execution: ");
	scanf("%lu", &first_execution);
	
	printf("Frequency: ");
	scanf("%lu", &frequency);

	action = TasksGetAction(action, key);

	curr_uid = SchedulerAddTask(curr_sched_struct->scheduler
					, action.action
					, params
					, (time_t)first_execution
					, frequency
					);

	AllocateForNewTaskUid(key, curr_uid, params, type);

	printf("\nTask Added\n");

	return CONTINUE;
}

/*****************************************************************************/

/* for CancelTask, RunScheduler and ClearScheduler */
static slist_iter_t UpdateTaskStructList(slist_iter_t runner)
{
	void *to_data = NULL;

	if (NULL != SListNext(curr_sched_struct->to))
	{
		to_data = SListGetData(curr_sched_struct->to);
	}

	free(SListGetData(runner));
	runner = SListRemove(runner);

	if (NULL == SListNext(runner) || to_data == SListGetData(runner))
	{
		curr_sched_struct->to = runner;
		if (!DListIsSameIterator(DListEnd(scheduler_list)
					, DListNext(scheduler_list_iter)))
		{
			((scheduler_struct_t *)(DListGetData(DListNext(
					scheduler_list_iter))))->from = runner;
		}
	}

	return runner;
}

/* for CancelTask only */
static int ResetTasksCmds(void *data, void *param)
{
	(void)param;

	--((task_struct_t *)data)->cmd; 

	return 0;
}

static int CancelTask(unsigned int key)
{
	slist_iter_t runner = curr_sched_struct->from;

	for (;!SListIsSameIterator(runner, curr_sched_struct->to)
		; runner = SListNext(runner))
	{
		if (((task_struct_t *)SListGetData(runner))->cmp(key
			, ((task_struct_t *)SListGetData(runner))->cmd))
		{
			SchedulerCancel(curr_sched_struct->scheduler
			, /*TaskGetUid(((task_struct_t *)SListGetData(runner))->task))*/
			((task_struct_t *)SListGetData(runner))->uid);
						
			runner = UpdateTaskStructList(runner);

			SListForEach(runner, curr_sched_struct->to
						, ResetTasksCmds, NULL);

			printf("\nTask Canceled\n");
			return CONTINUE;
		}
	}	

	printf("\nTask not found\n");
	return CONTINUE;
}

/*****************************************************************************/

/* for CancelTaskLogger */
static void PrintTasksInScheduler(void)
{
	slist_iter_t runner = curr_sched_struct->from;

	while (!SListIsSameIterator(runner, curr_sched_struct->to))
	{
		printf("%u-%s  ", ((task_struct_t *)SListGetData(runner))->cmd
			, ((task_struct_t *)SListGetData(runner))->task_name);
		runner = SListNext(runner);
	}
	printf("%lu-Return\n", SListSize(tasks_uid_list) + 1);
}

/* like SchedulerLogger, it lets the user choose the task desired to cancel */
int CancelTaskLogger(void)
{
	unsigned int key = 0;

	if (SchedulerIsEmpty(curr_sched_struct->scheduler))
	{
		printf("\nNo tasks to cancel in <%s>\n"
				, curr_sched_struct->name);
		return CONTINUE;
	}

	printf("\nTasks to Cancel:\n");
	PrintTasksInScheduler();

	scanf("%u", &key);

	if (key == SListSize(tasks_uid_list) + 1)
	{
		return CONTINUE;
	}

	return CancelTask(key);
}

/*****************************************************************************/

int RunScheduler(void)
{
	int check = 0;
	slist_iter_t runner = curr_sched_struct->from;
	slist_iter_t to = curr_sched_struct->to;

	printf("\nRunning:\n");

	check = SchedulerRun(curr_sched_struct->scheduler);

	if (1 == check)
	{
		size_t i = 1;
		sorted_list_iter_t sched_runner, end;

		sched_runner = SortedListBegin(PQToSortedList(SchedulerToQueue(
				curr_sched_struct->scheduler)));
		end = SortedListEnd(PQToSortedList(SchedulerToQueue(
				curr_sched_struct->scheduler)));
		
		for (; !SortedListIsSameIterator(sched_runner, end)
			; sched_runner = SortedListNext(sched_runner), ++i)
		{
			for (; !SListIsSameIterator(runner, to)
				&& !UIDIsSame(TaskGetUid((task_t *)
					SortedListGetData(sched_runner))
				, /*TaskGetUid(((task_struct_t *)SListGetData(runner))->task))*/
				((task_struct_t *)SListGetData(runner))->uid)
				; runner = SListNext(runner))
			{}

			if (!SListIsSameIterator(runner, to))
			{
				((task_struct_t *)SListGetData(runner))->cmd = i;
			}
		}

		runner = curr_sched_struct->from;

		while (!SListIsSameIterator(runner, to))
		{
			for (sched_runner = SortedListBegin(PQToSortedList(SchedulerToQueue(
				curr_sched_struct->scheduler)))
				; !SortedListIsSameIterator(sched_runner, end)
				&& !UIDIsSame(TaskGetUid((task_t *)
					SortedListGetData(sched_runner))
				, /*TaskGetUid(((task_struct_t *)SListGetData(runner))->task))*/
				((task_struct_t *)SListGetData(runner))->uid)
				; sched_runner = SortedListNext(sched_runner))
			{}
			if (SortedListIsSameIterator(sched_runner, end))
			{
				runner = UpdateTaskStructList(runner);
				to = curr_sched_struct->to;
			}
			else
			{
				runner = SListNext(runner);	
			}
		}
		
		printf("\nFinished because of 'stop'\n");		

		return CONTINUE;
	}	

	while (!SListIsSameIterator(runner, to))
	{
		runner = UpdateTaskStructList(runner);
		to = curr_sched_struct->to;
	}

	printf("\nFinished because is empty\n");

	return CONTINUE;
}

/*****************************************************************************/

int ClearScheduler(void)
{
	slist_iter_t runner = curr_sched_struct->from;

	if (SchedulerIsEmpty(curr_sched_struct->scheduler))
	{
		printf("\nNo tasks to clear in <%s>\n"
				, curr_sched_struct->name);
		return CONTINUE;
	}

	while (!SListIsSameIterator(runner, curr_sched_struct->to))
	{
		runner = UpdateTaskStructList(runner);
	}

	SchedulerClear(curr_sched_struct->scheduler);

	curr_sched_struct->to = curr_sched_struct->from;

	printf("\nCleared\n");
	
	return CONTINUE;
}

/*****************************************************************************/

/* for PrintTasksUidList only */
static void PrintParameter(slist_iter_t runner)
{
	switch (((task_struct_t *)SListGetData(runner))->type)
	{
	case 1:
		printf("Parameter: %d\n", 
			*(int *)((task_struct_t *)SListGetData(runner))->params);
		break;
	case 2:
		printf("Parameter: %f\n", 
			*(float *)((task_struct_t *)SListGetData(runner))->params);
		break;
	case 3:
		printf("Parameter: %c\n", 
			*(char *)((task_struct_t *)SListGetData(runner))->params);
		break;
	case 4: 
		printf("Parameter: %s\n", 
			(char *)((task_struct_t *)SListGetData(runner))->params);
		break;
	default:
		break;
	}
}

int PrintTasksUidList(void)
{
	slist_iter_t runner = curr_sched_struct->from;

	printf("\n********************* <%s>  Size: %lu *********************\n"
	, curr_sched_struct->name
	, SchedulerSize(curr_sched_struct->scheduler));

	while (!SListIsSameIterator(runner, curr_sched_struct->to))
	{
		printf("\n%u-%s  ", ((task_struct_t *)SListGetData(runner))->cmd
			, ((task_struct_t *)SListGetData(runner))->task_name);
		printf("Execution: %lu  "
		, TaskGetTime(((task_struct_t *)SListGetData(runner))->task));
		PrintParameter(runner);
		runner = SListNext(runner);
	}
	/*printf("\n*********************************************************\n");*/

	return CONTINUE;
}

/******************************************************************************/

scheduler_t *SchedStructToScheduler(scheduler_struct_t *sched_struct)
{
	assert(NULL != sched_struct);

	return sched_struct->scheduler;
}
