/****************************************************************************
Title: Sorted List
Author: Aviv Illoz
Description: Sorted list interface
****************************************************************************/

#include <stdio.h>		/* printf */
#include "sorted_list.h"	/* api */

#define DATA_SIZE 5

static int SortedListCmpInts(const void *iter, const void *data)
{
	return (*(int *)iter - *(int *)data);
}

static int SortedListIsMatchInts(const void *iter, const void *data)
{
	return (*(int *)iter == *(int *)data);
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

/******************************** MY FUNCS ***********************************/

static void SortedListIntPrint(sorted_list_t *sorted_list)
{
	sorted_list_iter_t runner = SortedListBegin(sorted_list);
	sorted_list_iter_t end = SortedListEnd(sorted_list);

	for (; !SortedListIsSameIterator(runner, end); runner = SortedListNext(runner))
	{
		printf("%d ", *(int *)SortedListGetData(runner));
	} 
	printf("\n");
}

/***********************************************************/

int main(void)
{
	sorted_list_t *sl1 = SortedListCreate(SortedListCmpInts);
	sorted_list_t *sl2 = SortedListCreate(SortedListCmpInts);
	sorted_list_iter_t iter_array[DATA_SIZE], iter;
	sorted_list_iter_t end = SortedListEnd(sl1);
	int data[DATA_SIZE] = {1,3,2,5,4};
	int data_test[DATA_SIZE] = {10,-10,3,7,8};
	size_t i = 0;

	printf("*********************** CREATED ***************************\n");

	printf("EMPTY? %d\n", SortedListIsEmpty(sl1));
	printf("SIZE: %lu\n", SortedListSize(sl1));

	printf("*********************** INSERT AND CHECK ***************************\n");

	for (; i < DATA_SIZE; ++i)
	{
		SortedListInsert(sl1, &data[i]);
	}

	printf("sl1: ");
	SortedListIntPrint(sl1);
	printf("EMPTY? %d\n", SortedListIsEmpty(sl1));
	printf("SIZE: %lu\n", SortedListSize(sl1));

	printf("*********************** ACCESS INDEX 3 ***************************\n");

	iter = SortedListBegin(sl1);
	for (i = 0; !SortedListIsSameIterator(iter, end); ++i, iter = SortedListNext(iter))
	{
		iter_array[i] = iter;
	}
	printf("INDEX 3 SHOULD BE 4: %d\n", *(int *)SortedListGetData(iter_array[3]));

	printf("*********************** ADD 10 FOR EACH ***************************\n");

	SortedListForEach(iter_array[0], end, Add, &data_test[0]); 
	printf("sl1: ");
	SortedListIntPrint(sl1);

	printf("*********************** SUBTRACT 10 FOR EACH ***************************\n");

	SortedListForEach(iter_array[0], end, Add, &data_test[1]); 
	printf("sl1: ");
	SortedListIntPrint(sl1);

	printf("*********************** FIND NUMBER 3 ***************************\n");

	iter = SortedListFind(sl1, iter_array[0], end, &data_test[2]);
	printf("FOUND: %d\n", *(int *)SortedListGetData(iter));

	printf("*********************** FIND NUMBER 3 NOT SORTED***************************\n");

	iter = SortedListFindIf(iter_array[0], end, SortedListIsMatchInts, &data_test[2]);
	printf("FOUND: %d\n", *(int *)SortedListGetData(iter));

	printf("*********************** REMOVE NUMBER 3 ***************************\n");

	SortedListRemove(iter);
	printf("sl1: ");
	SortedListIntPrint(sl1);
	
	printf("*********************** FIND NUMBER 3 ***************************\n");

	iter = SortedListFind(sl1, iter_array[0], end, &data_test[2]);
	printf("NOT FOUND: %p\n", SortedListGetData(iter));

	printf("*********************** FIND NUMBER 3 NOT SORTED***************************\n");

	iter = SortedListFindIf(iter_array[0], end, SortedListIsMatchInts, &data_test[2]);
	printf("NOT FOUND: %p\n", SortedListGetData(iter));	

	printf("*********************** POP BACK ***************************\n");

	printf("POP BACK: %d\n", *(int *)SortedListPopBack(sl1));
	printf("sl1: ");
	SortedListIntPrint(sl1);
	printf("EMPTY? %d\n", SortedListIsEmpty(sl1));
	printf("SIZE: %lu\n", SortedListSize(sl1));

	printf("*********************** POP FRONT ***************************\n");

	printf("POP FRONT: %d\n", *(int *)SortedListPopFront(sl1));
	printf("sl1: ");
	SortedListIntPrint(sl1);
	printf("EMPTY? %d\n", SortedListIsEmpty(sl1));
	printf("SIZE: %lu\n", SortedListSize(sl1));

	printf("*********************** INSERT AND CHECK sl2 ***************************\n");

	for (i = 0; i < DATA_SIZE; ++i)
	{
		SortedListInsert(sl2, &data[i]);
	}

	printf("sl2: ");
	SortedListIntPrint(sl2);
	printf("EMPTY? %d\n", SortedListIsEmpty(sl2));
	printf("SIZE: %lu\n", SortedListSize(sl2));

	printf("*********************** MERGE sl1 AND sl2 ***************************\n");

	SortedListMerge(sl1, sl2);
	printf("sl1: ");
	SortedListIntPrint(sl1);
	printf("sl2: ");
	SortedListIntPrint(sl2);
	printf("sl2 EMPTY? %d\n", SortedListIsEmpty(sl2));
	printf("sl2 SIZE: %lu\n", SortedListSize(sl2));

	printf("*********************** DESTROYING ***************************\n");

	SortedListDestroy(sl1);
	SortedListDestroy(sl2);

	return 0;
}
