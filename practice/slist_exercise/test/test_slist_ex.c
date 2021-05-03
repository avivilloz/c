/****************************************************************************
Title: Slist Exercise - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Peter
Description: Exercise implementing Slists and nodes
****************************************************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */
#include "slist_ex.h"	/* api */
#include "slist.h"	/* api */

struct slist_node
{
        void *data;            		
        struct slist_node *next;    	
};

struct slist
{
	slist_node_t *head;
	slist_node_t *tail;
};

/******************************************************************************************/

static void PrintIntListData(slist_iter_t head)
{
	slist_iter_t runner = head;

	assert(NULL != head);

	while (NULL != runner->next)
	{
		printf("%d ", *(int *)(runner->data));
		runner = runner->next;
	}
	printf("\n");
}

/******************************************************************************************/

int main(void)
{
	/*variables*/
	slist_t *list1, *list2, *list3;
	slist_iter_t iter, iter1, iter2, iter3 = malloc(sizeof(slist_node_t)), iter4;
	int a = 1, b = 2, c = 3, d = 4, e = 5;

	/*************************************************/

	/*create list1*/
	list1 = SListCreate();

	/*insert nodes to it*/
	SListInsert(list1->tail, &a);
	iter = SListInsert(list1->tail, &b);
	SListInsert(list1->tail, &c);
	SListInsert(list1->tail, &d);
	SListInsert(list1->tail, &e);

	/*flip and check*/
	list1->head = Flip(list1->head);
	printf("list1 flipped: ");
	PrintIntListData(list1->head);

	/*************************************************/

	/*create list2 with loop*/
	list2 = SListCreate();

	/*insert nodes to it*/
	SListInsert(list2->tail, &a);
	SListInsert(list2->tail, &b);
	iter1 = SListInsert(list2->tail, &c);
	iter2 = SListInsert(list2->tail, &d);
	iter3->next = iter1;
	iter2->next = iter3;

	/*check if there is loop in both lists*/
	printf("list1 has loop? %d\n", HasLoop(list1->head));
	printf("list2 has loop? %d\n", HasLoop(list2->head));

	/*************************************************/

	/*create list3 that intersects list1*/
	list3 = SListCreate();

	/*insert nodes to it*/
	SListInsert(list3->tail, &a);
	SListInsert(list3->tail, &b);
	iter4 = SListInsert(list3->tail, &c);
	iter4->next = iter;

	/*find intersection in lists*/
	printf("list1: ");
	PrintIntListData(list1->head);
	printf("list3: ");
	PrintIntListData(list3->head);
	printf("Intersection: ");
	PrintIntListData(FindIntersection(list1->head, list3->head));

	/*************************************************/

	/*destroy lists*/
	
	iter2->next = list2->tail;
	SListDestroy(list2);

	iter4->next = list3->tail;
	SListDestroy(list3);

	SListDestroy(list1);

	free(iter3);

	return 0;
}
