/*****************************************************************************
Title: 100K Threads - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Nathan
Description: 100K Threads
******************************************************************************/

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc, free */
#include <pthread.h>	/* thread functions */
#include <unistd.h>		/* sleep */
#include <time.h>		/* time */
#include <omp.h>

/********************************* TESTS *************************************/

typedef enum {TEST_PASS, TEST_FAIL} test_status_t;

#define expect(x) if (!(x)) {return TEST_FAIL;}

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

static test_status_t ThreadsEx1(void);
static void *FillIndex(void *index);

/* exercise 2 */

static test_status_t ThreadsEx2(void);

/* exercise 3 */

static test_status_t ThreadsEx3(void);

/* exercise 4 */

static test_status_t ThreadsEx4(void);
static void *SumOfDivisors(void *args);

/* exercise 5 */

static test_status_t ThreadsEx5(void);

/* exercise 6 */

static test_status_t ThreadsEx6(void);

/*****************************************************************************/

int main(void)
{
/*
	Test(ThreadsEx1(), "ThreadsEx1");
	Test(ThreadsEx2(), "ThreadsEx2");
	Test(ThreadsEx3(), "ThreadsEx3");
	Test(ThreadsEx4(), "ThreadsEx4");
*/	
	Test(ThreadsEx5(), "ThreadsEx5");
	Test(ThreadsEx6(), "ThreadsEx6");


	return 0;
}

/******************************** FUNCTIONS **********************************/
/* exercise 1 */

#define NUM_OF_THREADS 100000

static size_t INDEX_ARRAY[NUM_OF_THREADS];

static test_status_t ThreadsEx1(void)
{
	time_t start, end;
	size_t i = 0;
	pthread_t *threads = malloc(sizeof(pthread_t) * NUM_OF_THREADS);
	if (NULL == threads)
	{
		fputs("failed to allocate\n", stderr);
		return TEST_FAIL;
	}

	start = time(NULL);

	for (; i < NUM_OF_THREADS; ++i)
	{
		/* next exercise checks for error */
		pthread_create(&threads[i], NULL, FillIndex, (void *)(size_t)i);

		/* without join, it can create only until ulitmit -u or a little more */
		pthread_join(threads[i], NULL);
	}

	end = time(NULL);

	printf("time to create and run %d threads: %ld\n", NUM_OF_THREADS, end - start);
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		expect(i == INDEX_ARRAY[i]);
	}

	free(threads);

	return TEST_PASS;
}

static void *FillIndex(void *index)
{
	INDEX_ARRAY[(size_t)index] = (size_t)index;

	return NULL;
}

/* exercise 2 */

static test_status_t ThreadsEx2(void)
{
	time_t start, end;
	size_t i = 0;
	pthread_t *threads = malloc(sizeof(pthread_t) * NUM_OF_THREADS);
	if (NULL == threads)
	{
		fputs("failed to allocate\n", stderr);
		return TEST_FAIL;
	}

	start = time(NULL);

	for (; i < NUM_OF_THREADS; ++i)
	{
		while (0 != pthread_create(&threads[i], NULL, FillIndex, (void *)(size_t)i))
		{
			perror("Error");
			fputs("failed to create thread\n", stderr);
		}		
		
		/* whithout join we enter in an infinite loop */
		pthread_join(threads[i], NULL);
	}

	end = time(NULL);

	printf("time to create and run %d threads: %ld\n", NUM_OF_THREADS, end - start);
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		expect(i == INDEX_ARRAY[i]);
	}

	free(threads);

	return TEST_PASS;
}

/* exercise 3 */

static test_status_t ThreadsEx3(void)
{
	time_t start, end;
	size_t i = 0;
	pthread_attr_t attr;
	pthread_t *threads = malloc(sizeof(pthread_t) * NUM_OF_THREADS);
	if (NULL == threads)
	{
		fputs("failed to allocate\n", stderr);
		return TEST_FAIL;
	}

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	start = time(NULL);

	for (; i < NUM_OF_THREADS; ++i)
	{
		while (0 != pthread_create(&threads[i], &attr, FillIndex, (void *)(size_t)i))
		{
			perror("Error");
			fputs("failed to create thread\n", stderr);
		}
	}

	end = time(NULL);

	printf("time to create and run %d threads: %ld\n", NUM_OF_THREADS, end - start);
	
	pthread_attr_destroy(&attr);

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		expect(i == INDEX_ARRAY[i]);
	}

	free(threads);

	return TEST_PASS;
}

/* exercise 4 */

#define ULIMIT_NUM_OF_THREADS 31133
#define INPUT 3113300000
#define RANGE_SIZE (INPUT / ULIMIT_NUM_OF_THREADS)

static test_status_t ThreadsEx4(void)
{
	size_t i = 0;
	unsigned long *thread_val = NULL;
	unsigned long sum = 0;
	time_t start, end;
	pthread_attr_t attr;
	pthread_t *threads = malloc(sizeof(pthread_t) * ULIMIT_NUM_OF_THREADS);
	if (NULL == threads)
	{
		fputs("failed to allocate\n", stderr);
		return TEST_FAIL;
	}

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	start = time(NULL);

	for (; i < ULIMIT_NUM_OF_THREADS; ++i)
	{
		while (0 != pthread_create(&threads[i], &attr, SumOfDivisors, 
								   (void *)(unsigned long)i))
		{
			perror("Error");
			fputs("failed to create thread\n", stderr);
		}
	}

	for (i = 0; i < ULIMIT_NUM_OF_THREADS; ++i)
	{
		pthread_join(threads[i], (void *)&thread_val);
		sum += (unsigned long)thread_val;
	}
	
	end = time(NULL);

	printf("time to create and run %d threads: %ld\n", 
			ULIMIT_NUM_OF_THREADS, end - start);			

	printf("sum of divisors is: %lu\n", sum);

	pthread_attr_destroy(&attr);

	free(threads);

	return TEST_PASS;
}

static void *SumOfDivisors(void *index)
{
	size_t i = (size_t)index;
	unsigned long from = (RANGE_SIZE * i) + 1;
	unsigned long to = RANGE_SIZE * (i + 1);
	unsigned long sum = 0;

	for (; from <= to; ++from)
	{
		if (0 == (INPUT % from))
		{
			/*printf("%lu is divisible by %lu\n", INPUT, from);*/
			sum += from;
		}
	}

	return (void *)sum;
}

/* exercise 5 */

static test_status_t ThreadsEx5(void)
{
	unsigned long i = 1;
	unsigned long sum = 0;
	time_t start, end;

	start = time(NULL);

	for (; i <= INPUT; ++i)
	{
		if (0 == (INPUT % i))
		{
			/*printf("%lu is divisible by %lu\n", INPUT, i);*/
			sum += i;
		}
	}

	end = time(NULL);

	printf("time to calculate: %ld\n", end - start);

	printf("sum of divisors is: %lu\n", sum);

	return TEST_PASS;
}

/* exercise 6 */

static test_status_t ThreadsEx6(void)
{
	unsigned long i = 1;
	unsigned long sum = 0;
	time_t start, end;

	#pragma omp parallel

	start = time(NULL);

	for (; i <= INPUT; ++i)
	{
		if (0 == (INPUT % i))
		{
			/*printf("%lu is divisible by %lu\n", INPUT, i);*/
			#pragma omp critical
			sum += i;
		}
	}

	end = time(NULL);

	printf("time to calculate: %ld\n", end - start);

	printf("sum of divisors is: %lu\n", sum);

	return TEST_PASS;
}

/***************************** PSEUDO-CODE ***********************************/
