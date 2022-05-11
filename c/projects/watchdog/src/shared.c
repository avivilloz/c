/*****************************************************************************
Title: Shared
Author: Aviv Illoz
Description: Shared between client and watchdog
******************************************************************************/

#define _POSIX_C_SOURCE 200809L /* sigaction */
#define _GNU_SOURCE             /* secure_getenv, realpath */

#include <stdlib.h>             /* exit, getenv, setenv, realpath */
#include <stdio.h>              /* perror */
#include <errno.h>              /* errno */
#include <sys/sem.h>            /* sysv semaphores */
#include <string.h>             /* strcmp */
#include <unistd.h>             /* getpid, getppid */
#include <signal.h>             /* kill, sigaction */
#include <pthread.h>            /* pthread functions */

#include "scheduler.h"          /* scheduler functions */
#include "shared.h"             /* api */

/**************************** MACROS AND ENUMS *******************************/

#define CHILD 0
#define MAX_COUNT 5

enum repeat {ONCE = -1, FOREVER};

/*************************** UNIONS AND STRUCTS ******************************/

union semun 
{
    int val;
};

/*************************** STATIC VARIABLES ********************************/

static char *g_curr_process = NULL;

static pid_t g_partner_pid = 0;

static int g_argc = 0;
static char **g_argv = NULL;

static int g_semid = 0;
static int g_partner_sem = 0;
static struct sembuf g_increment_partner;
static struct sembuf g_decrement_own;

static scheduler_t *g_scheduler = NULL;
static size_t g_counter = 0;

static pthread_t g_check_status_thread;
static pthread_t g_scheduler_thread;

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t g_cv;

/**************************** HELPER FUNCTIONS  ******************************/

#define TASK_IS_BAD(is_good, error_msg) \
	if (0 == is_good) \
	{ \
		perror(error_msg); \
		pthread_cond_signal(&g_cv); \
		return ONCE; \
	}

#define THREAD_IS_BAD(is_good, error_msg) \
	if (0 == is_good) \
	{ \
		perror(error_msg); \
		pthread_cond_signal(&g_cv); \
		return NULL; \
	}

static void ExitIfBad(int is_good, int exit_value, const char *error_msg)
{
	if (!is_good)
	{
		perror(error_msg);
		exit(exit_value);
	}
}

static int IsBadUid(ilrd_uid_t uid)
{
	return 0 == uid.time && 0 == uid.pid && 0 == uid.counter; 
}

/*********************** STATIC FUNCTIONS DECLARATIONS ***********************/

static int CreatePartner(void);

static void InitSemBuffs(int own_sem);

static void *CheckStatusThread(void *ignored);
static void *SchedulerThread(void *ignored);

static int SigToPartner(void *ignored);
static int Count(void *ignored);
static int Stop(void *ignored);

/**************************** MAIN FUNCTIONS *********************************/

int SetGlobals(int argc, char *argv[], char *curr_process)
{
	int i = 2, j = 2;

	g_curr_process = curr_process;
	g_argc = argc;
	g_argv = malloc(argc * sizeof(char *));
	RETURN_IF_BAD((NULL != g_argv), "malloc() - Error");

	g_argv[0] = realpath(argv[1], NULL);
	RETURN_IF_BAD((NULL != g_argv[0]), "realpath() - Error");
	g_argv[1] = realpath(argv[0], NULL);
	RETURN_IF_BAD((NULL != g_argv[1]), "realpath() - Error");

	for (; j < argc; ++i, ++j)
	{
		g_argv[i] = argv[j];
	}

	return 0;
}

/*****************************************************************************/

int GetPartner(void)
{
	if (NULL == secure_getenv("PARENT"))
	{
		RETURN_IF_BAD((0 == setenv("PARENT", g_curr_process, 0)), "setenv() - Error");
	}

	if (0 != strcmp(secure_getenv("PARENT"), g_curr_process))
	{
		g_partner_pid = getppid();
		RETURN_IF_BAD((1 != g_partner_pid), "getppid() - Error (init is parent)");
	}
	else
	{
		RETURN_IF_BAD((0 == CreatePartner()), "CreatePartner() - Error");
	}

	return 0;
}

static int CreatePartner(void)
{
	g_partner_pid = fork();

	RETURN_IF_BAD((-1 != g_partner_pid), "fork() - Error");

	if (CHILD == g_partner_pid)
	{
		RETURN_IF_BAD((0 == execv(g_argv[0], g_argv)), "execv() - Error");
	}

	return 0;
}

/*****************************************************************************/

int PrepareSH(void (*signal_handler)(int, siginfo_t *, void *))
{
	struct sigaction action;

	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	RETURN_IF_BAD((0 == sigemptyset(&action.sa_mask)), "sigemptyset() - Error");

	RETURN_IF_BAD((0 == sigaction(SIGUSR1, &action, NULL)), "sigaction() - Error");
	RETURN_IF_BAD((0 == sigaction(SIGUSR2, &action, NULL)), "sigaction() - Error");

	return 0;
}

/*****************************************************************************/

int OpenSems(int own_sem)
{
	FILE *fp = NULL;
	key_t key = 0;

	/* when ressucitating partner, we use this variable to reset semaphore */ 
	g_partner_sem = !own_sem;

	InitSemBuffs(own_sem);

	fp = fopen("/tmp/watchdog_sem", "a+");
	RETURN_IF_BAD((NULL != fp), "fopen() - Error");
	fclose(fp);

	key = ftok("/tmp/watchdog_sem", 'a');
	RETURN_IF_BAD((-1 != key), "ftok() - Error");

	g_semid = semget(key, 2, 0777 | IPC_CREAT | IPC_EXCL);
	if (-1 == g_semid)
	{
		RETURN_IF_BAD((EEXIST == errno), "semget() - Error");

		g_semid = semget(key, 0, 0);
		RETURN_IF_BAD((-1 != g_semid), "semget() - Error");
	}
	else
	{
		union semun param;
		param.val = 0;

		RETURN_IF_BAD((-1 != semctl(g_semid, own_sem, SETVAL, param)), 
					  "semctl() - Error");
		RETURN_IF_BAD((-1 != semctl(g_semid, g_partner_sem, SETVAL, param)), 
					  "semctl() - Error");
	}

	return 0;
}

static void InitSemBuffs(int own_sem)
{
	g_increment_partner.sem_num = g_partner_sem;
	g_increment_partner.sem_op = 1;
	g_increment_partner.sem_flg = SEM_UNDO;

	g_decrement_own.sem_num = own_sem;
	g_decrement_own.sem_op = -1;
	g_decrement_own.sem_flg = SEM_UNDO;
}

/*****************************************************************************/

int CreateThreads(void)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	RETURN_IF_BAD((0 == pthread_create(&g_check_status_thread, &attr, 
				  CheckStatusThread, NULL)), "pthread_create() - Error");

	RETURN_IF_BAD((0 == pthread_create(&g_scheduler_thread, &attr, 
				  SchedulerThread, NULL)), "pthread_create() - Error");

	return 0;
}

static void *CheckStatusThread(void *ignored)
{
	ExitIfBad((0 == pthread_cond_init(&g_cv, NULL)), 1, "pthread_cond_init() - Error");

	ExitIfBad((0 == pthread_mutex_lock(&g_lock)), 3, "pthread_mutex_lock() - Error");
	ExitIfBad((0 == pthread_cond_wait(&g_cv, &g_lock)), 2,  "pthread_cond_wait() - Error");
	ExitIfBad((0 == pthread_mutex_unlock(&g_lock)), 4, "pthread_mutex_unlock() - Error");

	ExitIfBad((0 == kill(getpid(), SIGUSR2)), 5, "kill() - Error");

	return ignored;
}

static void *SchedulerThread(void *ignored)
{
	THREAD_IS_BAD((0 == Scheduler()), "RunScheduler() - Error");

	return ignored;	
}

/*****************************************************************************/

int Scheduler(void)
{
	ilrd_uid_t uid_status;

	g_scheduler = SchedulerCreate();
	RETURN_IF_BAD((NULL != g_scheduler), "SchedulerCreate() - Error");

	uid_status = SchedulerAddTask(g_scheduler, SigToPartner, NULL, 0, 1);
	RETURN_IF_BAD((!IsBadUid(uid_status)), "SchedulerAddTask() - Error");

	uid_status = SchedulerAddTask(g_scheduler, Count, NULL, 0, 1);
	RETURN_IF_BAD((!IsBadUid(uid_status)), "SchedulerAddTask() - Error");

	while (1)
	{
		/* temporary */
		printf("client sem:   %d\nwatchdog sem: %d\n", 
		semctl(g_semid, 0, GETVAL), semctl(g_semid, 1, GETVAL));

		/* wait for permission from watchdog to start scheduler */
		RETURN_IF_BAD((0 == semop(g_semid, &g_increment_partner, 1)), "semop() - Error");
		RETURN_IF_BAD((0 == semop(g_semid, &g_decrement_own, 1)), "semop() - Error");

		SchedulerRun(g_scheduler);
	}

	return 0;
}

/*************** TASKS ****************/

static int SigToPartner(void *ignored)
{
	int status = 0;

	/* temporary */
	printf("%s\n", g_curr_process);

	status = kill(g_partner_pid, SIGUSR1);
	if (0 != status)
	{
		TASK_IS_BAD((ESRCH == errno), "kill() - Error");
	}

	(void)ignored;

	return FOREVER;
}

static int Count(void *ignored)
{
	++g_counter;

	if (MAX_COUNT == g_counter)
	{
		ilrd_uid_t uid_status;		
		union semun param;
		
		/* temporary */
		printf("PARTNER OF %s DIED\n", g_curr_process);

		ResetCounter();

		/* make current process the parent */
		TASK_IS_BAD((0 == setenv("PARENT", g_curr_process, 1)), "setenv() - Error");

		/* create partner */
		TASK_IS_BAD((0 == GetPartner()), "CreatePartner() - Error");

		/* reset partner semaphore */
		param.val = 0;
		TASK_IS_BAD((-1 != semctl(g_semid, g_partner_sem, SETVAL, param)), 
					"semctl() - Error");

		/* stop scheduler */
		uid_status = SchedulerAddTask(g_scheduler, Stop, NULL, 0, 0);
		TASK_IS_BAD((!IsBadUid(uid_status)), "SchedulerAddTask() - Error");
	}

	(void)ignored;

	return FOREVER;
}

static int Stop(void *ignored)
{
	SchedulerStop(g_scheduler);
	
	(void)ignored;

	return ONCE;
}

/*****************************************************************************/

void ResetCounter(void)
{
	g_counter = 0;
}

/*****************************************************************************/

int DestroyPartnership(void)
{
	/* kill watchdog */
	RETURN_IF_BAD((0 == kill(g_partner_pid, SIGUSR2)), "kill() - Error");

	/* cancel threads */
	RETURN_IF_BAD((0 == pthread_cancel(g_check_status_thread)), 
				  "pthread_cancel() - Error");
	RETURN_IF_BAD((0 == pthread_cancel(g_scheduler_thread)), 
				  "pthread_cancel() - Error");

	/* destroy semaphores */
	RETURN_IF_BAD((-1 != semctl(g_semid, 0, IPC_RMID)), "semctl() - Error");

	SchedulerDestroy(g_scheduler);

	/* free memory allocated with realpath */
	free(g_argv[0]);
	g_argv[0] = NULL;
	
	free(g_argv[1]);
	g_argv[1] = NULL;

	free(g_argv);
	g_argv = NULL;	

	return 0;
}

/*****************************************************************************/

void WatchdogAutoDestroy(void)
{
	SchedulerDestroy(g_scheduler);

	/* free memory allocated with realpath */
	free(g_argv[0]);
	g_argv[0] = NULL;
	
	free(g_argv[1]);
	g_argv[1] = NULL;

	free(g_argv);
	g_argv = NULL;

	exit(0);
}

/*****************************************************************************/
