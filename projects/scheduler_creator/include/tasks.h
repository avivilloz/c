/****************************************************************************
Title: Tasks
Author: Aviv Illoz
Description: Tasks Interface
*****************************************************************************/

#ifndef	__TASKS_H__
#define	__TASKS_H__

/*****************************************************************************/

typedef struct tasks
{
	/*type - 1 for int, 2 for float, 3 for char, 4 for string*/
	unsigned int type;
	int (*action)(void *params);
	char *name;
} tasks_t;

#define TASK_ARRAY_SIZE 3
tasks_t task_array[TASK_ARRAY_SIZE];

/*****************************************************************************/

typedef struct action_temp
{
	int (*action)(void *params);
} action_temp_t;

/*****************************************************************************/

void InitializeTasksArray(void);

/*****************************************************************************/

void PrintTasks(void);

/*****************************************************************************/

action_temp_t TasksGetAction(action_temp_t action, unsigned int key);

/*****************************************************************************/

unsigned int TasksGetType(unsigned int key);

/********************************** TASKS ************************************/

/*1*/
int Stop(void *params);

/*2*/
int CallSystem(void *params);

/*3*/
int CurrTime(void *params);

/*****************************************************************************/

#endif	/*__TASKS_H__*/
