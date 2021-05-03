/****************************************************************************
Title: Dlist - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Igor
Description: Doubly Linked list interface
****************************************************************************/

#include <stdio.h>	/* printf */
#include "dlist.h"	/* api */
#define DATA_SIZE 6

/**************************************************************************/

static int IsMatch(const void *data, const void *element_to_find)
{
	return (*(int *)data == *(int *)element_to_find);
}

static int Add(void *data, void *param)
{
	if (NULL == data || NULL == param)
	{
		return 1;
	}

	*(int *)data += *(int *)param;

	return 0;
}

static void DListIntPrint(dlist_t *list)
{
	dlist_iter_t runner = DListBegin(list);

	for (; !DListIsSameIterator(runner, DListEnd(list))
		; runner = DListNext(runner))
	{
		printf("%d ", *(int *)DListGetData(runner));
	} 
	printf("\n");
}

/**************************************************************************/

int main(void)
{
	dlist_t *dl1 = DListCreate(), *dl2 = DListCreate();
	dlist_iter_t tail = DListEnd(dl1), iter_array[DATA_SIZE], iter;
	int data[DATA_SIZE] = {1, 2, 3, 4, 5, 2};
	int data_test[DATA_SIZE] = {3, 10, -10, 2, 1};
	size_t i = 0;

	printf("******************* AFTER CREATION OF dl1 ***********************\n");

	printf("EMPTY? %d\n", DListIsEmpty(dl1));
	printf("SIZE: %lu\n", DListSize(dl1));
	
	printf("********************* INSERTING AND CHECKING **********************\n");

	for (; i < DATA_SIZE; ++i)
	{
		iter_array[i] = DListInsert(tail, &data[i]);
	}

	printf("EMPTY? %d\n", DListIsEmpty(dl1));
	printf("SIZE: %lu\n", DListSize(dl1));
	printf("dl1: ");
	DListIntPrint(dl1);

	printf("********************** REMOVING AND CHECKING *************************\n");

	DListRemove(iter_array[3]);
	printf("EMPTY? %d\n", DListIsEmpty(dl1));
	printf("SIZE: %lu\n", DListSize(dl1));
	printf("dl1: ");
	DListIntPrint(dl1);
	
	printf("********************** INSERT BACK TO INDEX *************************\n");

	iter_array[3] = DListInsert(iter_array[4], &data[3]);
	printf("EMPTY? %d\n", DListIsEmpty(dl1));
	printf("SIZE: %lu\n", DListSize(dl1));
	printf("dl1: ");
	DListIntPrint(dl1);

	printf("********************** FIND 3 ************************\n");

	iter = DListFind(iter_array[0], iter_array[5], IsMatch, &data_test[0]);
	printf("FOUND: %d\n", *(int *)DListGetData(iter));

	printf("********************* FOR EACH ADD 10 ***************************\n");
	
	printf("CHECK FOR EACH: %d\n", DListForEach(iter_array[0], tail, Add, &data_test[1]));
	printf("dl1: ");
	DListIntPrint(dl1);

	printf("********************* FOR EACH SUBTRACT 10 ***************************\n");
	
	printf("CHECK FOR EACH: %d\n", DListForEach(iter_array[0], tail, Add, &data_test[2]));
	printf("dl1: ");
	DListIntPrint(dl1);

	printf("********************** MULTI FIND ************************\n");

	printf("CHECK MULTI FIND: %d\n", DListMultiFind(iter_array[0], tail, IsMatch, &data_test[3], dl2));
	printf("dl2: ");
	DListIntPrint(dl2);

	printf("********************** PUSH 1 TO FRONT OF dl2 **************************\n");

	DListPushFront(dl2, &data_test[4]);
	printf("dl2: ");
	DListIntPrint(dl2);

	printf("********************** PUSH 3 TO BACK OF dl2 **************************\n");

	DListPushBack(dl2, &data_test[0]);
	printf("dl2: ");
	DListIntPrint(dl2);

	printf("********************* POP FRONT OF dl2 ****************************\n");

	printf("POP: %d\n", *(int *)DListPopFront(dl2));
	printf("dl2: ");
	DListIntPrint(dl2);

	printf("********************* POP BACK OF dl2 ****************************\n");

	printf("POP: %d\n", *(int *)DListPopBack(dl2));
	printf("dl2: ");
	DListIntPrint(dl2);

	printf("********************* SPLICE dl1 TO dl2 **************************\n");

	iter = DListBegin(dl2);
	DListSplice(DListBegin(dl1), DListEnd(dl1), iter);
	printf("dl1: ");
	DListIntPrint(dl1);
	printf("SIZE dl1: %lu\n", DListSize(dl1));
	printf("dl2: ");
	DListIntPrint(dl2);
	printf("SIZE dl2: %lu\n", DListSize(dl2));

	printf("********************** DESTROYING **********************\n");

	DListDestroy(dl1);
	DListDestroy(dl2);
	
	return 0;
}
