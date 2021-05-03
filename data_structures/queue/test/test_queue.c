/*******************************************************************************
* Title: Queue - Infinity Labs R&D 
* Group: Ol91
* Author: Aviv
* Reviewer: Ezequiel
* Description: Queue interface
********************************************************************************/

#include <stdio.h>	/*printf*/
#include <assert.h>	/*assert*/
#include "queue.h"	/*api*/
#include "slist.h"	/*api*/

/********************************************************************************/

static void PrintIntListData(queue_t *queue)
{
	size_t i = QSize(queue);
	void *front = NULL;

	for (; i > 0; --i)
	{
		front = QFront(queue);
		printf("%d ", *(int *)front);
		QDequeue(queue);
	}
	printf("\n");
}

/********************************************************************************/

int main(void)
{
	queue_t *q = QCreate(), *q2 = QCreate();
	int a = 58, b = 25, c = 44, d = 60;

	/*****************************************/

	printf("Queue created!\n");
	printf("Empty? %d\n", QIsEmpty(q));

	/*****************************************/

	QEnqueue(q, &a);
	QEnqueue(q, &b);
	QEnqueue(q, &c);
	printf("After adding 3 nodes, Size: %lu\n", QSize(q));	
	printf("Empty? %d\n", QIsEmpty(q));

	/*****************************************/

	printf("Element to be Dequeued: %d\n", *(int *)QFront(q));

	/*****************************************/

	QDequeue(q);
	printf("Dequeued!\nNew element to be Dequeued: %d\n", *(int *)QFront(q));	
	printf("Empty? %d\n", QIsEmpty(q));
	printf("Size after Dequeueing: %lu\n", QSize(q));

	/*****************************************/

	QEnqueue(q2, &d);
	QEnqueue(q2, &c);
	QEnqueue(q2, &b);
	QEnqueue(q2, &a);

	QAppend(q, q2);

	printf("After appending: ");
	PrintIntListData(q);	

	/*****************************************/

	QDestroy(q);
	QDestroy(q2);
	printf("Destroyed!\n");

	return 0;
}


