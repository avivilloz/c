/****************************************************************************
Title: PQ Heap - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Igor
Description: PQ Heap API
*****************************************************************************/

#include <stdlib.h>		/* malloc, free */
#include <assert.h>		/* assert */

#include "pq_heap.h"		/* api */

/*****************************************************************************/

struct pq
{
	heap_t *heap;	
};

/*****************************************************************************/

pq_t *PQCreate(int (*priority_cmp)(const void *lhs, const void *rhs))
{
	pq_t *new_pq = (pq_t *)malloc(sizeof(pq_t));
	if (NULL == new_pq)
	{
		return NULL;
	}

	new_pq->heap = HeapCreate(priority_cmp);
	if (NULL == new_pq->heap)
	{
		free(new_pq);
		new_pq = NULL;
		return NULL;
	}

	return new_pq;
}

/*****************************************************************************/

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);	

	HeapDestroy(pq->heap);

	free(pq);
	pq = NULL;
}

/*****************************************************************************/

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);

	return HeapPush(pq->heap, data);
}

/*****************************************************************************/

void *PQDequeue(pq_t *pq)
{
	void *peek = NULL;

	assert(NULL != pq);

	peek = HeapPeek(pq->heap);

	HeapPop(pq->heap);

	return peek;
}

/*****************************************************************************/

void *PQFront(const pq_t *pq)
{
	assert(NULL != pq);

	return HeapPeek(pq->heap);
}

/*****************************************************************************/

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);

	return HeapSize(pq->heap);
}

/*****************************************************************************/

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);

	return HeapIsEmpty(pq->heap);
}

/*****************************************************************************/

void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

/*****************************************************************************/

void *PQErase(pq_t *pq, is_match_t is_match, void *params)
{
	assert(NULL != pq);	

	return HeapRemove(pq->heap, is_match, params);
}

/*****************************************************************************/
