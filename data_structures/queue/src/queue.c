/*******************************************************************************
* Title: Queue
* Author: Aviv Illoz
* Description: Queue interface
*******************************************************************************/

#include <stdio.h>	/*printf*/
#include <stdlib.h>	/*malloc*/
#include <assert.h>	/*assert*/

#include "queue.h"	/*api*/
#include "slist.h"	/*api*/

struct queue
{
    	slist_t *list;
};

/******************************************************************************/

queue_t *QCreate(void)
{
	slist_t *list = NULL;
	queue_t *queue = NULL;

	list = SListCreate();
	if (NULL == list)
	{
		return NULL;
	}

	queue = malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		free(list);
		list = NULL;
		return NULL;
	}

	queue->list = list;

	return queue;
}

/******************************************************************************/

void QDestroy(queue_t *queue)
{
	assert(NULL != queue);

	SListDestroy(queue->list);

	free(queue);
	queue = NULL;
}

/******************************************************************************/

int QEnqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);

	return (NULL == SListInsert(SListEnd(queue->list), data));
}

/******************************************************************************/

void QDequeue(queue_t *queue)
{
	assert(NULL != queue);

	SListRemove(SListBegin(queue->list));
}

/******************************************************************************/

void *QFront(const queue_t *queue)
{
	assert(NULL != queue);

	return SListGetData(SListBegin(queue->list));
}

/******************************************************************************/

int QIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);

	return SListIsEmpty(queue->list);
}

/******************************************************************************/

size_t QSize(const queue_t *queue)
{
	assert(NULL != queue);	

	return SListSize(queue->list);
}

/******************************************************************************/

void QAppend(queue_t *dest, queue_t *src)
{
	SListAppend(dest->list, src->list);
}

/******************************************************************************/
