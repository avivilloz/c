/***************************************************************************
Title: PriorityQueue
Author: Aviv Illoz
Description: Priority Queue interface header file
*****************************************************************************/

#ifndef __PQ_H__
#define __PQ_H__

#include <stddef.h>     	/* typedef & size_t */
#include "sorted_list.h"	/* api */

typedef struct pq pq_t;

/*****************************************************************************/
/*
Decription: Create new queue_t queue, highest priority at the front		

Time Complexity: O(1)		

*/
pq_t *PQCreate(int (*priority_cmp)(const void *lhs, const void *rhs));

/*****************************************************************************/
/*
Decription: Destroy queue_t queue
		
Time Complexity: O(1)		
*/
void PQDestroy(pq_t *pq);

/*****************************************************************************/
/*
Decription: Enqueue into the queue		
	
Time Complexity: O(n)	

*/
int PQEnqueue(pq_t *pq, void *data);

/*****************************************************************************/
/*
Decription: Dequeue from the queue		
		
Time Complexity: O()

*/
void *PQDequeue(pq_t *pq);

/*****************************************************************************/
/*
Decription: Points to the element that is going to be deqeueued		
	
Time Complexity: O(1)	

*/
void *PQFront(const pq_t *pq);
 
/*****************************************************************************/
/*
Decription: Get size of a Queue		

Time complexity: O(n)	

*/
size_t PQSize(const pq_t *pq);

/*****************************************************************************/
/*
Decription: 1 if Queue is empty, O if not		

Time Complexity: O(1)	

*/
int PQIsEmpty(const pq_t *pq);

/*****************************************************************************/
/*
Decription: Clear the queue without destroying it		

Time Complexity: O(n)	

*/
void PQClear(pq_t *pq);
/*****************************************************************************/
/*
Decription: Erase the element. To find the exact element to erase the is_match function is used. 		

Time Complexity: O(n)	

*/

void *PQErase(pq_t *pq, int(*is_match)(const void *data, const void *params), void *params);

sorted_list_t *PQToSortedList(pq_t *pq);

#endif /*__PQ_H__*/
