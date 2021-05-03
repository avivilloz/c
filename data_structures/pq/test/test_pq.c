/****************************************************************************
Title: PriorityQueue - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: David
Description: Priority Queue interface header file
*****************************************************************************/

#include <stdio.h>	/* printf */
#include "pq.h"		/* api */

static int IsMatch(const void *lhs, const void *rhs)
{
	return (*(int *)lhs == *(int *)rhs);
}

static int PQCmp(const void *lhs, const void *rhs)
{
	if (*(int *)lhs % 5 == 0 && *(int *)rhs % 5 != 0)
	{
		return -1;
	}

	if (*(int *)lhs % 5 == 0 && *(int *)rhs % 5 == 0)
	{
		if (*(int *)lhs > *(int *)rhs)
		{
			return 0;
		}
	}

	return 1;
}

static void PQPrint(pq_t *pq)
{
/***** SIZE, ISEMPTY, DEQUEUE ********************/

	size_t size = PQSize(pq), i = 0;
	printf("Size: %lu\n", size);
	printf("Empty? %d\n", PQIsEmpty(pq));
	for (; i < size; ++i)
	{
		printf("%d ", *(int *)PQDequeue(pq));
	}
	printf("\n");
}

int main(void)
{
/************* CREATE, ENQUEUE *******************/	

	pq_t *pq1 = PQCreate(PQCmp);
	int data[6] = {3,10,12,15,13,20};
	size_t i = 0;

	for (; i < 6; ++i)
	{
		PQEnqueue(pq1, &data[i]);
	}

	PQPrint(pq1);

/************ ERASE ******************************/

	for (i = 0; i < 6; ++i)
	{
		PQEnqueue(pq1, &data[i]);
	}

	PQErase(pq1, IsMatch, &data[3]);
	PQPrint(pq1);

/************** CLEAR, FRONT *********************/
	
	for (i = 0; i < 6; ++i)
	{
		PQEnqueue(pq1, &data[i]);
	}

	printf("Front: %d\n", *(int *)PQFront(pq1));

	PQClear(pq1);
	PQPrint(pq1);

/************* DESTROY ***************************/

	PQDestroy(pq1);
	
	return 0;
}

