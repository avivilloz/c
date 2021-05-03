/****************************************************************************
Title: Sorted List - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Sebastian
Description: Sorted list interface
****************************************************************************/

#include <stdio.h>		/* printf */
#include <assert.h>		/* assert */
#include <stdlib.h>		/* malloc, free */
#include "dlist.h"		/* api */
#include "sorted_list.h"	/* api */

struct sorted_list
{
	dlist_t *list;
	int (*cmp)(const void *lhs, const void *rhs);
};

/*****************************************************************************/

sorted_list_t *SortedListCreate(int (*cmp)(const void *lhs, const void *rhs))
{
	sorted_list_t *new_list = malloc(sizeof(sorted_list_t));
	if (NULL == new_list)
	{
		return NULL;
	}

	new_list->list = DListCreate();
	if (NULL == new_list->list)
	{
		free(new_list);
		new_list = NULL;
		return NULL;
	}

	new_list->cmp = cmp;
	
	return new_list;	
}

/*****************************************************************************/

void SortedListDestroy(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);

	DListDestroy(sorted_list->list);
	sorted_list->list = NULL;
	
	free(sorted_list);
	sorted_list = NULL;
}

/*****************************************************************************/

sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	sorted_list_iter_t iter;
	dlist_iter_t runner;
	dlist_iter_t end;	 

	assert(NULL != sorted_list);

	runner = DListBegin(sorted_list->list);
	end = DListEnd(sorted_list->list);	

	for (; !DListIsSameIterator(runner, end) 
		&& sorted_list->cmp(DListGetData(runner), data) <= 0
		; runner = DListNext(runner))
	{}

	/*iter.sorted_list = sorted_list;*/
	iter.iterator = DListInsert(runner, data);

	return iter;
}

/*****************************************************************************/

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
	iter.iterator = DListRemove(iter.iterator);

	return iter;
}

/*****************************************************************************/

sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t begin;

	assert(NULL != sorted_list);

	begin.iterator = DListBegin(sorted_list->list);

	return begin;
}

/*****************************************************************************/

sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t end;

	assert(NULL != sorted_list);

	end.iterator = DListEnd(sorted_list->list);

	return end;
}

/*****************************************************************************/

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
	iter.iterator = DListNext(iter.iterator);

	return iter;
}

/*****************************************************************************/

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	iter.iterator = DListPrev(iter.iterator);

	return iter;
}

/*****************************************************************************/
 
int SortedListIsSameIterator(sorted_list_iter_t lhs, sorted_list_iter_t rhs)
{
	return DListIsSameIterator(lhs.iterator, rhs.iterator);
}

/*****************************************************************************/

void *SortedListGetData(sorted_list_iter_t iter)
{
	return DListGetData(iter.iterator);
}

/*****************************************************************************/

void *SortedListPopFront(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);

	return DListPopFront(sorted_list->list);	
}

/*****************************************************************************/

void *SortedListPopBack(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);

	return DListPopBack(sorted_list->list);
}

/*****************************************************************************/

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);

	return DListIsEmpty(sorted_list->list);
}

/*****************************************************************************/

size_t SortedListSize(const sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);

	return DListSize(sorted_list->list);
}

/*****************************************************************************/

int SortedListForEach(
	sorted_list_iter_t from,
	sorted_list_iter_t to,
	int (*action)(void *data, void *param), 
	void *param
	)
{
	return DListForEach(from.iterator, to.iterator, action, param);
}

/*****************************************************************************/

sorted_list_iter_t SortedListFind(
	sorted_list_t *sorted_list,
	sorted_list_iter_t from,
	sorted_list_iter_t to,
	const void *element_to_find
	)
{
	dlist_iter_t runner = from.iterator;
	int check = -1;

	assert(NULL != sorted_list);
	
	for (; !DListIsSameIterator(runner, to.iterator) && check < 0
		; runner = DListNext(runner))
	{
		check = sorted_list->cmp(DListGetData(runner), element_to_find);
		if (0 == check)
		{
			to.iterator = runner;
		}
	}

	return to;
}

/*****************************************************************************/

sorted_list_iter_t SortedListFindIf(
	sorted_list_iter_t from,
	sorted_list_iter_t to,
	int (*is_match)(const void *data, const void *element_to_find),
	const void *element_to_find
	)
{
	to.iterator = DListFind(from.iterator, 
				to.iterator, 
				is_match, 
				element_to_find);
	return to;
}

/*****************************************************************************/

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	dlist_iter_t runner1, runner2;
	dlist_iter_t dest_end, src_end;
	dlist_iter_t from, to;

	assert(NULL != dest && NULL != src);

	runner1 = DListBegin(dest->list);
	runner2 = DListBegin(src->list);
	dest_end = DListEnd(dest->list);
	src_end = DListEnd(src->list);
	
	while (!DListIsSameIterator(runner2, src_end))
	{
		from = runner2;

		while (!DListIsSameIterator(runner1, dest_end)
			&& !DListIsSameIterator(runner2, src_end) 
			&& dest->cmp(DListGetData(runner2), 
					DListGetData(runner1)) > 0)
		{
			runner1 = DListNext(runner1);
		}

		if (!DListIsSameIterator(runner1, dest_end))
		{
			DListSplice(runner2, src_end, dest_end);
			break;
		}

		while (!DListIsSameIterator(runner2, src_end)
			&& !DListIsSameIterator(runner1, dest_end)
			&& src->cmp(DListGetData(runner1), 
					DListGetData(DListNext(runner2))) > 0)
		{
			runner2 = DListNext(runner2);
		}
	
		to = runner2;
		runner2 = DListNext(runner2);
		DListSplice(from, to, runner1);
	}
}





