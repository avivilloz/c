/*******************************************************************************
* Title: Slist
* Author: Aviv Illoz
* Description: Linked List interface
********************************************************************************/

#include <stdio.h>	/* printf */
#include "slist.h"	/* api */

/*******************************************************************************/

static int IsMatch(const void *data, const void *element_to_find)
{
	return (data != element_to_find);
}

static int AddTwoNums(void *n1, void *n2)
{
	*(int *)n1 += *(int *)n2;

	return 0;
}

/*******************************************************************************/

int main(void)
{	
	slist_t *l = SListCreate();
	slist_iter_t begin, end, next, i1, i2, i3, find;
	int a = 58, b = 25, c = 44, d = 60;

	/*****************************************/

	printf("Slist created!\n");
	printf("Empty? %d\n", SListIsEmpty(l));

	/*****************************************/

	i1 = SListInsert(SListEnd(l), &a);
	i2 = SListInsert(SListEnd(l), &b);
	i3 = SListInsert(SListEnd(l), &c);
	printf("After adding 3 nodes, Size: %lu\n", SListSize(l));	
	printf("Empty? %d\n", SListIsEmpty(l));

	/*****************************************/

	printf("Data i1 which was set to 'a': %d\n", *(int *)SListGetData(i1));
	SListSetData(i1, &d);
	printf("Data i1 after setting to 'd': %d\n", *(int *)SListGetData(i1));
	printf("Data i2 set to 'b': %d\n", *(int *)SListGetData(i2));
	printf("Data i3 set to 'c': %d\n", *(int *)SListGetData(i3));

	/*****************************************/

	begin = SListBegin(l);
	end = SListEnd(l);
	next = SListNext(i3);
	printf("Are begin and end equal? %d\n", SListIsSameIterator(begin, end));
	printf("Are next of i3 and end equal? %d\n", SListIsSameIterator(next, end));

	/*****************************************/

	printf("Find number 44:\n");
	find = SListFind(i1, i3, IsMatch, &c);
	printf("Is %d your number?\n", *(int *)SListGetData(find));

	/*****************************************/

	SListForEach(i1, i3, AddTwoNums, &b);
	printf("Data i1 after adding 25: %d\n", *(int *)SListGetData(i1));
	printf("Data i2 after adding 25: %d\n", *(int *)SListGetData(i2));
	printf("Data i3 after adding 25: %d\n", *(int *)SListGetData(i3));

	/*****************************************/

	/*setting i2, which was freed in the function, to the same node as i1*/
	i2 = SListRemove(i1);
	next = SListNext(i1);
	printf("i2 and i1 are (after removing i1): %d, %d\n", *(int *)SListGetData(i2), *(int *)SListGetData(i1));
	printf("Are i2 and i1 equal? %d\n", SListIsSameIterator(i3, SListEnd(l)));
	printf("i3 is (after removing i1): %d\n", *(int *)SListGetData(i3));
	printf("next of i1 is: %d\n", *(int *)SListGetData(next));	
	printf("Empty? %d\n", SListIsEmpty(l));
	printf("Size after removing i1: %lu\n", SListSize(l));

	/*****************************************/

	printf("Removing i3: \n");	
	i3 = SListRemove(i3);
	printf("Empty? %d\n", SListIsEmpty(l));
	printf("Size after removing i3: %lu\n", SListSize(l));
	printf("Are i3 and end equal? %d\n", SListIsSameIterator(i3, SListEnd(l)));

	/*****************************************/

	SListDestroy(l);
	printf("Destroyed!\n");

	return 0;
}
