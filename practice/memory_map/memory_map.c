#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_OF_THREADS 20

typedef struct node
{
	size_t index;
	struct node *next;
} node_t;

typedef struct list
{
	node_t *head;
	node_t *tail;
} list_t;

static size_t index = 0;
static list_t indexes;

static void ExitIfBad(int is_good, int exit_value, const char *error_msg)
{
	if (!is_good)
	{
		perror(error_msg);
		exit(exit_value);
	}
}

static void *PushBack(void *param)
{
	size_t var1 = 1;	/* for checking address */
	float var2 = 25.5;	/* for checking address */
	int var3 = 0;		/* for checking catch */
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	ExitIfBad(NULL != new_node, 1, "Error");

	new_node->index = index;
	new_node->next = NULL;
	
	++index;

	if (NULL == indexes.head)
	{
		indexes.head = new_node;
		indexes.tail = new_node;
		return param;
	}

	indexes.tail->next = new_node;
	indexes.tail = new_node;

	/*fprintf(stdout, "%lu\n", var1 + (size_t)var2);  ->using random variables */

	/*sleep(60);  ->make threads sleep, so they don't finish before analized */

/*
*/
	var2 = (float)(var1 / var3);

	printf("%f\n", var2);

	return param;
}

static void PrintList(void)
{
	node_t *curr = indexes.head;

	for (; curr != NULL; curr = curr->next)
	{
		printf("%lu ", curr->index);
	}
	putchar('\n');
}

int main(void)
{
	size_t i = 0;
	pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_THREADS);
	ExitIfBad(NULL != threads, 1, "Error");

	indexes.head = NULL;
	indexes.tail = NULL;

	for (; i < NUM_OF_THREADS; ++i)
	{
		ExitIfBad(0 == pthread_create(&threads[i], NULL, PushBack, NULL), 2, "Error");
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		ExitIfBad(0 == pthread_join(threads[i], NULL), 3, "Error");
	}

	PrintList();

	return 0;
}
