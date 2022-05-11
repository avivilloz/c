#include <stdlib.h>

#include "fsq.h"

struct fsq
{
	size_t capacity;
	size_t write_index;
	size_t read_index;
	size_t *queue;
};

fsq_t *FSQCreate(size_t capacity)
{
	fsq_t *new_fsq = (fsq_t *)malloc(sizeof(fsq_t));
	if (NULL == new_fsq)
	{
		return NULL;
	}

	new_fsq->queue = (size_t *)malloc(capacity * sizeof(size_t));
	if (NULL == new_fsq->queue)
	{
		return NULL;
	}

	new_fsq->capacity = capacity + 1;
	new_fsq->write_index = 0;
	new_fsq->read_index = 0;

	return new_fsq;
}

void FSQDestroy(fsq_t *fsq)
{
	free(fsq->queue);
	fsq->queue = NULL;
	
	free(fsq);
	fsq = NULL;
}

int FSQIsFull(fsq_t *fsq)
{
	return (((fsq->write_index + 1) % fsq->capacity) == fsq->read_index);
}

int FSQIsEmpty(fsq_t *fsq)
{
	return (fsq->write_index == fsq->read_index);
}

size_t FSQDequeue(fsq_t *fsq)
{
	size_t pop_index = fsq->read_index;

	fsq->read_index = (fsq->read_index + 1) % fsq->capacity;

	return fsq->queue[pop_index];
}

void FSQEnqueue(fsq_t *fsq, size_t data)
{
	fsq->queue[fsq->write_index] = data;
	fsq->write_index = (fsq->write_index + 1) % fsq->capacity;
}
