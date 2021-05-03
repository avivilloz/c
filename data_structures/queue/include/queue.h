/*******************************************************************************
* Title: Queue - Infinity Labs R&D 
* Group: Ol91
* Description: Queue interface
********************************************************************************/

#ifndef __QUEUE_INFITY_OL_91__
#define __QUEUE_INFITY_OL_91__
#include <stddef.h> 	/* size_t */
#include "slist.h"	/* slist_iter_t */

/*
struct queue
{
    slist_t *list;
};
*/

typedef struct queue queue_t;
/*****************************************************************************/
/*
Decription: Create new queue_t queue		

Time Complexity: 0(1)		

*/
queue_t *QCreate(void);
/*****************************************************************************/
/*
Decription: Destroy queue_t queue
		
Time Complexity: 0(1)		
*/
void QDestroy(queue_t *queue);
/*****************************************************************************/
/*
Decription: Enqueue into the queue		
	
Time Complexity: 0(1)	

*/
int QEnqueue(queue_t *queue, void *data);
/*****************************************************************************/
/*
Decription: Dequeue from the queue		
		
Time Complexity: 0(n)

*/
void QDequeue(queue_t *queue);
/*****************************************************************************/
/*
Decription: Points to the element that is going to be deqeueued		
	
Time Complexity: 0(1)	

*/
void *QFront(const queue_t *queue);
/*****************************************************************************/
/*
Decription: Bool if Queue is empty		

Time Complexity: 0(1)	

*/
int QIsEmpty(const queue_t *queue);
/*****************************************************************************/
/*
Decription: Get size of a Queue		

Time complexity: 0(n)	

*/
size_t QSize(const queue_t *queue);
/*****************************************************************************/
/*
Decription: Append together two Queues one after another		

Time complexity: 0(1)	

*/
void QAppend(queue_t *dest, queue_t *src);

#endif /* __QUEUE_INFITY_OL_91__ */

