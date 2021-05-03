/****************************************************************************
Title: PriorityQueue - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: David
Description: Priority Queue interface header file
*****************************************************************************/

#include <stdlib.h>		/* malloc, free */
#include <assert.h>		/* assert */
#include "sorted_list.h"	/* api */
#include "pq.h"			/* api */

struct pq
{
	sorted_list_t *sorted_list;	
};

/*****************************************************************************/

pq_t *PQCreate(int (*priority_cmp)(const void *lhs, const void *rhs))
{
	pq_t *new_pq = (pq_t *)malloc(sizeof(pq_t));
	if (NULL == new_pq)
	{
		return NULL;
	}

	new_pq->sorted_list = SortedListCreate(priority_cmp);
	if (NULL == new_pq->sorted_list)
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

	SortedListDestroy(pq->sorted_list);
	free(pq);
	pq = NULL;
}

/*****************************************************************************/

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);

	return (SortedListIsSameIterator(SortedListInsert(pq->sorted_list, data),
		SortedListEnd(pq->sorted_list)));
}

/*****************************************************************************/

void *PQDequeue(pq_t *pq)
{
	assert(NULL != pq);	

	return SortedListPopFront(pq->sorted_list);
}

/*****************************************************************************/

void *PQFront(const pq_t *pq)
{
	assert(NULL != pq);

	return SortedListGetData(SortedListBegin(pq->sorted_list));
}

/*****************************************************************************/

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);

	return SortedListSize(pq->sorted_list);
}

/*****************************************************************************/

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);

	return SortedListIsEmpty(pq->sorted_list);
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

void *PQErase(pq_t *pq, int(*is_match)(const void *data, const void *params), void *params)
{
	sorted_list_iter_t begin, tail, temp;
	void *data = NULL;

	assert(NULL != pq);	

	begin = SortedListBegin(pq->sorted_list);
	tail = SortedListEnd(pq->sorted_list);
	temp = SortedListFindIf(begin, tail, is_match, params);
	if (!SortedListIsSameIterator(temp, tail))
	{
		data = SortedListGetData(temp);	
		SortedListRemove(temp);
	}	

	return data;
}

/*****************************************************************************/

sorted_list_t *PQToSortedList(pq_t *pq)
{
	assert(NULL != pq);
	
	return pq->sorted_list;
}
