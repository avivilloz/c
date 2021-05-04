/*****************************************************************************
Title: Producer-Consumer
Author: Aviv Illoz
Description: Producer-Consumer Exercises
List of Exit Values:
	1-allocation fails
	2-pthread_create
	3-pthread_join
	4-pthread_mutex_lock
	5-pthread_mutex_unlock
	6-sem_open
	7-sem_post
	8-sem_wait
	9-pthread_cond_init
	10-fopen
	11-ftok
	12-semget
	13-semctl
	14-semop
	15-pthread_cond_broadcast
	16-pthread_cond_wait
******************************************************************************/

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc, free */
#include <errno.h>		/* perror */
#include <string.h>		/* strlen */
#include <unistd.h>		/* sleep */
#include <pthread.h>	/* thread related functions */
#include <fcntl.h>		/* for O_* constants */
#include <sys/stat.h>	/* for mode constants */
#include <semaphore.h>	/* for POSIX semahores */
#include <sys/sem.h>	/* for SYSTEM V semaphores */

#include "queue.h"		/* queue related functions for list execises */
#include "dlist.h"		/* dlist related functions for CQ */
#include "fsq.h"		/* fsq related functions for FSQ exercises */

/********************************* TESTS *************************************/

typedef enum {TEST_PASS, TEST_FAIL} test_status_t;

static void Test(test_status_t func_test, char *func_name)
{
	if (TEST_FAIL == func_test)
	{
		printf("%s: \33[5;1;31mFAILURE\33[0m\n", func_name);
	}
	else
	{
		printf("%s: \33[5;1;32;1mSUCCESS\33[0m\n", func_name);
	}
}

/************************** FUNCTION DECLARATIONS ****************************/

/* exercise 1 */

static test_status_t Ex1(void);
static void *WriteEx1(void *param);
static void *ReadEx1(void *param);

/* exercise 2 */

static test_status_t Ex2(void);
static void *WriteEx2(void *param);
static void *ReadEx2(void *param);

/* exercise 2_2 */

static test_status_t Ex2_2(void);
static void *WriteEx2_2(void *param);
static void *ReadEx2_2(void *param);

/* exercise 3 */

static test_status_t Ex3(void);
static void *WriteEx3(void *param);
static void *ReadEx3(void *param);

/* exercise 3_2 */

static test_status_t Ex3_2(void);
static void *WriteEx3_2(void *param);
static void *ReadEx3_2(void *param);

/* exercise 4 */

static test_status_t Ex4(void);
static void *WriteEx4(void *param);
static void *ReadEx4(void *param);

/* exercise 4_2 */

static test_status_t Ex4_2(void);
static void *WriteEx4_2(void *param);
static void *ReadEx4_2(void *param);

/* exercise 5 */

static test_status_t Ex5(void);
static void *WriteEx5(void *param);
static void *ReadEx5(void *param);
static void SemaphoreCreate(void);
static void InitSemBuffers(void);

/************************ MACROS AND GLOBAL VARIABLES ************************/

#define NUM_OF_EXCHANGES 80000000
#define NUM_OF_PRODUCERS 50
#define NUM_OF_CONSUMERS 8
#define BUFFER_SIZE 50
#define FSQ_CAPACITY 50
#define CQ_CAPACITY 50

static char g_buffer[BUFFER_SIZE];
static queue_t *g_indexes;
static dlist_t *g_indexes_cq;
static fsq_t *g_indexes_fsq;

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_producer_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_consumer_lock = PTHREAD_MUTEX_INITIALIZER;

static sem_t *g_semaphore;
static sem_t *g_producer_sem;
static sem_t *g_consumer_sem;

static size_t g_producer_counter = CQ_CAPACITY;
static size_t g_consumer_counter = 0;

static int g_buffer_is_full = 0;

/* for ex5 */

union semun 
{
    int val;	/* used for SETVAL only */
};

static size_t g_buffer_ex5[1];
static struct sembuf g_increment;
static struct sembuf g_decrement;
static int g_semid_ex5;
static pthread_cond_t g_cv_ex5;

/***************************** HELPER FUNCTIONS ******************************/

static void ExitIfBad(int is_good, int exit_value, const char *error_msg)
{
	if (!is_good)
	{
		perror(error_msg);
		exit(exit_value);
	}
}

static char *Itoa(unsigned long n)
{
	size_t i = 0, j = 0, check = 1;

	char *str = NULL;

	while (check <= n)
	{
		check *= 10;
		++i;
	}

	str = malloc(i + 1);

	for (; i > 0; --i, ++j)
	{
		str[j] = ((n % check) / (check / 10)) + 48;
		
		check /= 10;
	}

	str[j] = '\0';

	return str;
}

/*****************************************************************************/

int main(void)
{
/*
	Test(Ex1(), "Ex1");
	Test(Ex2(), "Ex2");
	Test(Ex2_2(), "Ex2_2");
	Test(Ex3(), "Ex3");
	Test(Ex3_2(), "Ex3_2");
	Test(Ex4(), "Ex4");
	Test(Ex4_2(), "Ex4_2");
*/
	Test(Ex5(), "Ex5");

	return 0;
}

/******************************* FUNCTIONS ***********************************/

static test_status_t Ex1(void)
{
	pthread_t producer;
	pthread_t consumer;

	while (0 != pthread_create(&producer, NULL, WriteEx1, NULL))
	{
		ExitIfBad(EAGAIN == errno, 2, "Error");
	}

	while (0 != pthread_create(&consumer, NULL, ReadEx1, NULL))
	{
		ExitIfBad(EAGAIN == errno, 2, "Error");
	}

	ExitIfBad(0 == pthread_join(producer, NULL), 3, "Error");	
	ExitIfBad(0 == pthread_join(consumer, NULL), 3, "Error");	
	
	return TEST_PASS;
}

static void *WriteEx1(void *param)
{
	unsigned long i = 0;
	char *str_to_write = "times copied: ";
	
	while(1)
	{
		if (!__atomic_load_n(&g_buffer_is_full, __ATOMIC_ACQUIRE))
		{
			strcpy(g_buffer, str_to_write);
			strcat(g_buffer, Itoa(i));

			++i;

			__atomic_add_fetch(&g_buffer_is_full, 1, __ATOMIC_ACQUIRE);
		}
	}

	return param;
}

static void *ReadEx1(void *param)
{
	while(1)
	{
		if (__atomic_load_n(&g_buffer_is_full, __ATOMIC_ACQUIRE))
		{
			fprintf(stdout, "%s\n", g_buffer);

			__atomic_sub_fetch(&g_buffer_is_full, 1, __ATOMIC_ACQUIRE);
		}
	}

	return param;
}

/*****************************************************************************/

static test_status_t Ex2(void)
{
	pthread_t *consumers = NULL;
	pthread_t *producers = NULL; 
	size_t i = 0;

	producers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_PRODUCERS);
	ExitIfBad(NULL != producers, 1, "Error");

	consumers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_CONSUMERS);
	ExitIfBad(NULL != consumers, 1, "Error");

	g_indexes = QCreate();
	ExitIfBad(NULL != g_indexes, 1, "Error");

	for (; i < NUM_OF_PRODUCERS || i < NUM_OF_CONSUMERS; ++i)
	{
		if (i < NUM_OF_PRODUCERS)
		{
			while (0 != pthread_create(&producers[i], NULL, WriteEx2, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
		
		if (i < NUM_OF_CONSUMERS)
		{
			while (0 != pthread_create(&consumers[i], NULL, ReadEx2, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		ExitIfBad(0 == pthread_join(producers[i], NULL), 3, "Error");
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		ExitIfBad(0 == pthread_join(consumers[i], NULL), 3, "Error");	
	}

	QDestroy(g_indexes);

	free(producers);
	producers = NULL;
	
	free(consumers);
	consumers = NULL;

	return TEST_PASS;
}

static void* WriteEx2(void *param)
{
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == pthread_mutex_lock(&g_lock), 4, "Error");

		ExitIfBad(0 == QEnqueue(g_indexes, (void *)(size_t)param), 1, "Error");

		ExitIfBad(0 == pthread_mutex_unlock(&g_lock), 5, "Error");
	}

	return NULL;
}

static void* ReadEx2(void *consumer_index)
{
	int was_read = 0;	
	size_t producer_index = 0;
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == pthread_mutex_lock(&g_lock), 4, "Error");

		if (!QIsEmpty(g_indexes))
		{
			producer_index = (size_t)QFront(g_indexes);
			QDequeue(g_indexes);
			was_read = 1;
		}

		ExitIfBad(0 == pthread_mutex_unlock(&g_lock), 5, "Error");
		
		if (was_read)
		{
			fprintf(stdout, "producer %lu, was read by consumer %lu\n", 
					producer_index, (size_t)consumer_index);
			was_read = 0;
		}
	}

	return NULL;
}

/*****************************************************************************/

static test_status_t Ex2_2(void)
{
	pthread_t *consumers = NULL;
	pthread_t *producers = NULL;
	size_t i = 0;

	producers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_PRODUCERS);
	ExitIfBad(NULL != producers, 1, "Error");

	consumers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_CONSUMERS);
	ExitIfBad(NULL != consumers, 1, "Error");

	sem_unlink("/sem_ex2");

	g_semaphore = sem_open("/sem_ex2", O_CREAT, 0777, 0);
	ExitIfBad(SEM_FAILED != g_semaphore, 6, "Error");

	g_indexes = QCreate();
	ExitIfBad(NULL != g_indexes, 1, "Error");

	for (; i < NUM_OF_PRODUCERS || i < NUM_OF_CONSUMERS; ++i)
	{
		if (i < NUM_OF_PRODUCERS)
		{
			while (0 != pthread_create(&producers[i], NULL, WriteEx2_2, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
		
		if (i < NUM_OF_CONSUMERS)
		{
			while (0 != pthread_create(&consumers[i], NULL, ReadEx2_2, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		ExitIfBad(0 == pthread_join(producers[i], NULL), 3, "Error");
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		ExitIfBad(0 == pthread_join(consumers[i], NULL), 3, "Error");	
	}

	sem_close(g_semaphore);
	sem_unlink("/sem_ex2");

	QDestroy(g_indexes);

	free(producers);
	producers = NULL;
	
	free(consumers);
	consumers = NULL;

	return TEST_PASS;
}

static void* WriteEx2_2(void *param)
{
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == pthread_mutex_lock(&g_lock), 4, "Error");

		ExitIfBad(0 == QEnqueue(g_indexes, (void *)(size_t)param), 1, "Error");

		ExitIfBad(0 == pthread_mutex_unlock(&g_lock), 5, "Error");
		ExitIfBad(0 == sem_post(g_semaphore), 7, "Error");
	}

	return NULL;
}

static void* ReadEx2_2(void *consumer_index)
{
	size_t producer_index = 0;
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == sem_wait(g_semaphore), 8, "Error");
		ExitIfBad(0 == pthread_mutex_lock(&g_lock), 4, "Error");

		producer_index = (size_t)QFront(g_indexes);
		QDequeue(g_indexes);

		ExitIfBad(0 == pthread_mutex_unlock(&g_lock), 5, "Error");
		
		fprintf(stdout, "producer %lu, was read by consumer %lu\n", 
				producer_index, (size_t)consumer_index);
	}

	return NULL;
}

/*****************************************************************************/

static test_status_t Ex3(void)
{
	pthread_t *consumers = NULL;
	pthread_t *producers = NULL;
	size_t i = 0;

	producers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_PRODUCERS);
	ExitIfBad(NULL != producers, 1, "Error");

	consumers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_CONSUMERS);
	ExitIfBad(NULL != consumers, 1, "Error");

	sem_unlink("/prod_sem_ex3");
	sem_unlink("/cons_sem_ex3");

	g_producer_sem = sem_open("/prod_sem_ex3", O_CREAT, 0777, FSQ_CAPACITY);
	ExitIfBad(SEM_FAILED != g_producer_sem, 6, "Error");

	g_consumer_sem = sem_open("/cons_sem_ex3", O_CREAT, 0777, 0);
	ExitIfBad(SEM_FAILED != g_consumer_sem, 6, "Error");

	g_indexes_fsq = FSQCreate(FSQ_CAPACITY);
	ExitIfBad(NULL != g_indexes_fsq, 1, "Error");

	for (; i < NUM_OF_PRODUCERS || i < NUM_OF_CONSUMERS; ++i)
	{
		if (i < NUM_OF_PRODUCERS)
		{
			while (0 != pthread_create(&producers[i], NULL, WriteEx3, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
		
		if (i < NUM_OF_CONSUMERS)
		{
			while (0 != pthread_create(&consumers[i], NULL, ReadEx3, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		ExitIfBad(0 == pthread_join(producers[i], NULL), 3, "Error");
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		ExitIfBad(0 == pthread_join(consumers[i], NULL), 3, "Error");	
	}

	sem_close(g_producer_sem);
	sem_unlink("/prod_sem_ex3");

	sem_close(g_consumer_sem);
	sem_unlink("/cons_sem_ex3");

	FSQDestroy(g_indexes_fsq);

	free(producers);
	producers = NULL;
	
	free(consumers);
	consumers = NULL;

	return TEST_PASS;
}

static void* WriteEx3(void *param)
{
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == sem_wait(g_producer_sem), 8, "Error");
		ExitIfBad(0 == pthread_mutex_lock(&g_lock), 4, "Error");

		FSQEnqueue(g_indexes_fsq, (size_t)param);

		ExitIfBad(0 == pthread_mutex_unlock(&g_lock), 5, "Error");
		ExitIfBad(0 == sem_post(g_consumer_sem), 7, "Error");
	}

	return NULL;
}

static void* ReadEx3(void *consumer_index)
{
	size_t producer_index = 0;
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == sem_wait(g_consumer_sem), 8, "Error");
		ExitIfBad(0 == pthread_mutex_lock(&g_lock), 4, "Error");

		producer_index = FSQDequeue(g_indexes_fsq);

		ExitIfBad(0 == pthread_mutex_unlock(&g_lock), 5, "Error");
		ExitIfBad(0 == sem_post(g_producer_sem), 7, "Error");		

		fprintf(stdout, "producer %lu, was read by consumer %lu\n", 
				producer_index, (size_t)consumer_index);
	}

	return NULL;
}

/*****************************************************************************/

static test_status_t Ex3_2(void)
{
	pthread_t *consumers = NULL;
	pthread_t *producers = NULL;
	size_t i = 0;

	producers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_PRODUCERS);
	ExitIfBad(NULL != producers, 1, "Error");

	consumers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_CONSUMERS);
	ExitIfBad(NULL != consumers, 1, "Error");

	sem_unlink("/prod_sem_ex3");
	sem_unlink("/cons_sem_ex3");

	g_producer_sem = sem_open("/prod_sem_ex3", O_CREAT, 0777, FSQ_CAPACITY);
	ExitIfBad(SEM_FAILED != g_producer_sem, 6, "Error");

	g_consumer_sem = sem_open("/cons_sem_ex3", O_CREAT, 0777, 0);
	ExitIfBad(SEM_FAILED != g_consumer_sem, 6, "Error");

	g_indexes_fsq = FSQCreate(FSQ_CAPACITY);
	ExitIfBad(NULL != g_indexes_fsq, 1, "Error");

	for (; i < NUM_OF_PRODUCERS || i < NUM_OF_CONSUMERS; ++i)
	{
		if (i < NUM_OF_PRODUCERS)
		{
			while (0 != pthread_create(&producers[i], NULL, WriteEx3_2, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
		
		if (i < NUM_OF_CONSUMERS)
		{
			while (0 != pthread_create(&consumers[i], NULL, ReadEx3_2, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		ExitIfBad(0 == pthread_join(producers[i], NULL), 3, "Error");
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		ExitIfBad(0 == pthread_join(consumers[i], NULL), 3, "Error");	
	}

	sem_close(g_producer_sem);
	sem_unlink("/prod_sem_ex3");

	sem_close(g_consumer_sem);
	sem_unlink("/cons_sem_ex3");

	FSQDestroy(g_indexes_fsq);

	free(producers);
	producers = NULL;
	
	free(consumers);
	consumers = NULL;

	return TEST_PASS;
}

static void* WriteEx3_2(void *param)
{
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == sem_wait(g_producer_sem), 8, "Error");
		ExitIfBad(0 == pthread_mutex_lock(&g_producer_lock), 4, "Error");

		FSQEnqueue(g_indexes_fsq, (size_t)param);

		ExitIfBad(0 == pthread_mutex_unlock(&g_producer_lock), 5, "Error");
		ExitIfBad(0 == sem_post(g_consumer_sem), 7, "Error");
	}

	return NULL;
}

static void* ReadEx3_2(void *consumer_index)
{
	size_t producer_index = 0;
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == sem_wait(g_consumer_sem), 8, "Error");
		ExitIfBad(0 == pthread_mutex_lock(&g_consumer_lock), 4, "Error");

		producer_index = FSQDequeue(g_indexes_fsq);

		ExitIfBad(0 == pthread_mutex_unlock(&g_consumer_lock), 5, "Error");
		ExitIfBad(0 == sem_post(g_producer_sem), 7, "Error");		

		fprintf(stdout, "producer %lu, was read by consumer %lu\n", 
				producer_index, (size_t)consumer_index);
	}

	return NULL;
}

/*****************************************************************************/

static test_status_t Ex4(void)
{
	pthread_t *consumers = NULL;
	pthread_t *producers = NULL;
	size_t i = 0;

	producers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_PRODUCERS);
	ExitIfBad(NULL != producers, 1, "Error");

	consumers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_CONSUMERS);
	ExitIfBad(NULL != consumers, 1, "Error");

	g_indexes_cq = DListCreate();
	ExitIfBad(NULL != g_indexes_cq, 1, "Error");

	for (; i < NUM_OF_PRODUCERS || i < NUM_OF_CONSUMERS; ++i)
	{
		if (i < NUM_OF_PRODUCERS)
		{
			while (0 != pthread_create(&producers[i], NULL, WriteEx4, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
		
		if (i < NUM_OF_CONSUMERS)
		{
			while (0 != pthread_create(&consumers[i], NULL, ReadEx4, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		ExitIfBad(0 == pthread_join(producers[i], NULL), 3, "Error");
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		ExitIfBad(0 == pthread_join(consumers[i], NULL), 3, "Error");	
	}

	DListDestroy(g_indexes_cq);

	free(producers);
	producers = NULL;
	
	free(consumers);
	consumers = NULL;

	return TEST_PASS;
}

static void* WriteEx4(void *param)
{
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == pthread_mutex_lock(&g_lock), 4, "Error");

		if (0 == __atomic_load_n(&g_producer_counter, __ATOMIC_ACQUIRE))
		{
			__atomic_add_fetch(&g_producer_counter, 1, __ATOMIC_ACQUIRE);
			__atomic_sub_fetch(&g_consumer_counter, 1, __ATOMIC_ACQUIRE);
			DListPopFront(g_indexes_cq);
		}
	
		__atomic_sub_fetch(&g_producer_counter, 1, __ATOMIC_ACQUIRE);
		__atomic_add_fetch(&g_consumer_counter, 1, __ATOMIC_ACQUIRE);
		DListPushBack(g_indexes_cq, param);

		ExitIfBad(0 == pthread_mutex_unlock(&g_lock), 5, "Error");
	}

	return NULL;
}

static void* ReadEx4(void *consumer_index)
{
	int was_read = 0;
	size_t producer_index = 0;
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == pthread_mutex_lock(&g_lock), 4, "Error");
		
		if (__atomic_load_n(&g_consumer_counter, __ATOMIC_ACQUIRE) > 0)
		{
			__atomic_sub_fetch(&g_consumer_counter, 1, __ATOMIC_ACQUIRE);
			__atomic_add_fetch(&g_producer_counter, 1, __ATOMIC_ACQUIRE);
			producer_index = (size_t)DListPopFront(g_indexes_cq);
			was_read = 1;
		}

		ExitIfBad(0 == pthread_mutex_unlock(&g_lock), 5, "Error");
		
		if (was_read)
		{
			fprintf(stdout, "producer %lu, was read by consumer %lu\n", 
					producer_index, (size_t)consumer_index);
			was_read = 0;
		}
	}

	return NULL;
}

/*****************************************************************************/

static test_status_t Ex4_2(void)
{
	pthread_t *consumers = NULL;
	pthread_t *producers = NULL;
	size_t i = 0;

	producers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_PRODUCERS);
	ExitIfBad(NULL != producers, 1, "Error");

	consumers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_CONSUMERS);
	ExitIfBad(NULL != consumers, 1, "Error");

	g_indexes_fsq = FSQCreate(FSQ_CAPACITY);
	ExitIfBad(NULL != g_indexes_fsq, 1, "Error");

	for (; i < NUM_OF_PRODUCERS || i < NUM_OF_CONSUMERS; ++i)
	{
		if (i < NUM_OF_PRODUCERS)
		{
			while (0 != pthread_create(&producers[i], NULL, WriteEx4_2, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
		
		if (i < NUM_OF_CONSUMERS)
		{
			while (0 != pthread_create(&consumers[i], NULL, ReadEx4_2, 
										(void *)(size_t)i))
			{
				ExitIfBad(EAGAIN == errno, 2, "Error");
			}
		}
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		ExitIfBad(0 == pthread_join(producers[i], NULL), 3, "Error");
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		ExitIfBad(0 == pthread_join(consumers[i], NULL), 3, "Error");	
	}

	FSQDestroy(g_indexes_fsq);

	free(producers);
	producers = NULL;
	
	free(consumers);
	consumers = NULL;

	return TEST_PASS;
}

static void* WriteEx4_2(void *param)
{
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == pthread_mutex_lock(&g_producer_lock), 4, "Error");

		FSQEnqueue(g_indexes_fsq, (size_t)param);

		ExitIfBad(0 == pthread_mutex_lock(&g_consumer_lock), 4, "Error");

		while (FSQIsFull(g_indexes_fsq))
		{
			FSQDequeue(g_indexes_fsq);
		}

		ExitIfBad(0 == pthread_mutex_unlock(&g_consumer_lock), 5, "Error");
		ExitIfBad(0 == pthread_mutex_unlock(&g_producer_lock), 5, "Error");
	}

	return NULL;
}

static void* ReadEx4_2(void *consumer_index)
{
	int was_read = 0;
	size_t producer_index = 0;
	size_t i = 0;

	for (; i < NUM_OF_EXCHANGES; ++i)
	{
		ExitIfBad(0 == pthread_mutex_lock(&g_producer_lock), 4, "Error");
		ExitIfBad(0 == pthread_mutex_lock(&g_consumer_lock), 4, "Error");

		if (!FSQIsEmpty(g_indexes_fsq))
		{
			ExitIfBad(0 == pthread_mutex_unlock(&g_producer_lock), 5, "Error");
			producer_index = FSQDequeue(g_indexes_fsq);
			was_read = 1;
		}
		else
		{
			ExitIfBad(0 == pthread_mutex_unlock(&g_producer_lock), 5, "Error");
		}

		ExitIfBad(0 == pthread_mutex_unlock(&g_consumer_lock), 5, "Error");

		if (was_read)
		{
			fprintf(stdout, "producer %lu, was read by consumer %lu\n", 
					producer_index, (size_t)consumer_index);
			was_read = 0;
		}
	}

	return NULL;
}

/*****************************************************************************/

static test_status_t Ex5(void)
{
	pthread_t *consumers = NULL;
	pthread_t *producers = NULL;
	size_t i = 0;

	producers = (pthread_t *)malloc(sizeof(pthread_t));
	ExitIfBad(NULL != producers, 1, "Error");

	consumers = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_CONSUMERS);
	ExitIfBad(NULL != consumers, 1, "Error");

	SemaphoreCreate();
	InitSemBuffers();

	ExitIfBad(0 == pthread_cond_init(&g_cv_ex5, NULL), 9, "Error");

	while (0 != pthread_create(&producers[i], NULL, WriteEx5, NULL))
	{
		ExitIfBad(EAGAIN == errno, 2, "Error");
	}

	for (; i < NUM_OF_CONSUMERS; ++i)
	{
		while (0 != pthread_create(&consumers[i], NULL, ReadEx5, 
								   (void *)(size_t)i))
		{
			ExitIfBad(EAGAIN == errno, 2, "Error");
		}
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		ExitIfBad(0 == pthread_join(producers[i], NULL), 3, "Error");
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		ExitIfBad(0 == pthread_join(consumers[i], NULL), 3, "Error");	
	}

	free(producers);
	producers = NULL;
	
	free(consumers);
	consumers = NULL;

	return TEST_PASS;
}

static void SemaphoreCreate(void)
{
	FILE *fp = NULL;
	key_t key = 0;
	union semun param;

	fp = fopen("/tmp/sem_ex5", "a+");
	ExitIfBad(NULL != fp, 10, "Error");
	fclose(fp);

	key = ftok("/tmp/sem_ex5", 'a');
	ExitIfBad(-1 != key, 11, "Error");

	g_semid_ex5 = semget(key, 1, 0777 | IPC_CREAT);
	ExitIfBad(-1 != g_semid_ex5, 12, "Error");

	param.val = 0;
	ExitIfBad(-1 != semctl(g_semid_ex5, 0, SETVAL, param), 13, "Error");
}

static void InitSemBuffers(void)
{
	g_increment.sem_flg = SEM_UNDO;
	g_increment.sem_num = 0;
	g_increment.sem_op = 1;

	g_decrement.sem_flg = SEM_UNDO;
	g_decrement.sem_num = 0;
	g_decrement.sem_op = -(NUM_OF_CONSUMERS);
}

static void* WriteEx5(void *param)
{
	size_t data = 0;

	while (1)
	{
		ExitIfBad(0 == semop(g_semid_ex5, &g_decrement, 1), 14, "Error");
		ExitIfBad(0 == pthread_mutex_lock(&g_lock), 4, "Error");
		*g_buffer_ex5 = data;
		ExitIfBad(0 == pthread_cond_broadcast(&g_cv_ex5), 15, "Error");
		ExitIfBad(0 == pthread_mutex_unlock(&g_lock), 5, "Error");

		fputs("producer released!\n", stdout);

		++data;
	} 

	return NULL;
}

static void* ReadEx5(void *consumer_index)
{
	size_t data = 0;

	while (1)
	{
		ExitIfBad(0 == pthread_mutex_lock(&g_lock), 4, "Error");
		ExitIfBad(0 == semop(g_semid_ex5, &g_increment, 1), 14, "Error");
		ExitIfBad(0 == pthread_cond_wait(&g_cv_ex5, &g_lock), 16, "Error");
		ExitIfBad(0 == pthread_mutex_unlock(&g_lock), 5, "Error");
		data = *g_buffer_ex5;

		fprintf(stdout, "data %lu, was read by consumer %lu\n", 
				data, (size_t)consumer_index);
	}

	return NULL;
}

/*****************************************************************************/
