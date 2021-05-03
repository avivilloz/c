/****************************************************************************
Title: Dlist - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Igor
Description: Doubly Linked list interface
****************************************************************************/

#include <stdlib.h>	/* malloc */
#include <stdio.h>	/* printf for personal func */
#include <assert.h>	/* assert */
#include "dlist.h"	/* api */

struct dlist_node
{
        void *data;
        struct dlist_node *next;
        struct dlist_node *prev;
};

struct dlist
{
	dlist_node_t head;
	dlist_node_t tail;
};

/*****************************************************************************/

#ifndef NDEBUG
static dlist_node_t *IterToNode(dlist_iter_t iter)
{
	return iter.dlist_node;
}

/*
static dlist_iter_t NodeToIter(dlist_node_t *node)
{
	dlist_iter_t iter; 
	iter.dlist_node = node;

	return iter;
}
*/

static int IsSameAsEnd(dlist_iter_t iterator)
{
	return (NULL == IterToNode(iterator)->next);
}

static int IsSameAsBegin(dlist_iter_t iterator)
{
	return (NULL == IterToNode(iterator)->prev->prev);
}
#endif

/*****************************************************************************/

dlist_t *DListCreate(void)
{
	dlist_t *new_dlist = malloc(sizeof(dlist_t));
	if (NULL == new_dlist)
	{
		return NULL;
	}

	new_dlist->head.data = (void *)0xDEADBEEF;
	new_dlist->head.prev = NULL;
	new_dlist->head.next = &new_dlist->tail;

	new_dlist->tail.data = (void *)0xDEADBEEF;
	new_dlist->tail.prev = &new_dlist->head;
	new_dlist->tail.next = NULL;

	return new_dlist;	
}

/*****************************************************************************/

void DListDestroy(dlist_t *list)
{
	dlist_node_t *runner = list->head.next, *temp = runner;

	assert(NULL != list);

	while (runner != &list->tail)
	{
		runner = runner->next;
		free(temp);
		temp = runner;
	}

	free(list);
	list = NULL;
}

/*****************************************************************************/

dlist_iter_t DListBegin(const dlist_t *list)
{
	dlist_iter_t begin;
	
	assert(NULL != list);

	begin.dlist_node = ((dlist_t *)list)->head.next;

	return begin;
}

/*****************************************************************************/

dlist_iter_t DListEnd(const dlist_t *list)
{
	dlist_iter_t end;

	assert(NULL != list);

	end.dlist_node = &((dlist_t *)list)->tail;	

	return end;
}

/*****************************************************************************/

dlist_iter_t DListNext(dlist_iter_t iterator)
{
	dlist_iter_t next;
	assert(!IsSameAsEnd(iterator));
	next.dlist_node = iterator.dlist_node->next;

	return next;
}

/*****************************************************************************/

dlist_iter_t DListPrev(dlist_iter_t iterator)
{
	dlist_iter_t prev;
	assert(!IsSameAsBegin(iterator));
	prev.dlist_node = iterator.dlist_node->prev;

	return prev;
}

/*****************************************************************************/ 
         
int DListIsSameIterator(dlist_iter_t lhs, dlist_iter_t rhs)
{
	return (lhs.dlist_node == rhs.dlist_node);
}

/*****************************************************************************/

void *DListGetData(dlist_iter_t iterator)
{
	return iterator.dlist_node->data;
}

/*****************************************************************************/

void DListSetData(dlist_iter_t iterator, void *data)
{
	iterator.dlist_node->data = data;
}

/*****************************************************************************/

dlist_iter_t DListInsert(dlist_iter_t iterator, void *data)
{
	dlist_node_t *new_node = NULL;

	assert(NULL != iterator.dlist_node->prev);

	new_node = malloc(sizeof(dlist_node_t));
	if (NULL == new_node)
	{
		free(new_node);
		for (; NULL != iterator.dlist_node->next
			; iterator = DListNext(iterator))
		{}
		return iterator;
	}

	new_node->next = iterator.dlist_node;
	new_node->prev = iterator.dlist_node->prev;
	new_node->data = data;

	iterator.dlist_node->prev->next = new_node;
	iterator.dlist_node->prev = new_node;

	iterator.dlist_node = new_node;

	return iterator;
}

/*****************************************************************************/

dlist_iter_t DListRemove(dlist_iter_t iterator)
{	
	dlist_node_t *temp = iterator.dlist_node->next;
	
	assert(!IsSameAsEnd(iterator));

	iterator.dlist_node->next->prev = iterator.dlist_node->prev; 
	iterator.dlist_node->prev->next = iterator.dlist_node->next;

	free(iterator.dlist_node);
	iterator.dlist_node = temp;

	return iterator;
}

/*****************************************************************************/

size_t DListSize(const dlist_t *list)
{
	size_t size = 0;
	dlist_node_t *runner = ((dlist_t *)list)->head.next;

	assert(NULL != list);

	for (; runner != &list->tail; runner = runner->next, ++size)
	{}

	return size;
}

/*****************************************************************************/

int DListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);

	return (list->head.next == &list->tail);
}

/*****************************************************************************/

dlist_iter_t DListFind(
    dlist_iter_t from,
    dlist_iter_t to,
    int (*is_match)(const void *data, const void *element_to_find),
    const void *element_to_find
)
{
	dlist_iter_t runner;
	int check = 0;
	runner.dlist_node = from.dlist_node;
	
	for (; runner.dlist_node != to.dlist_node && 0 == check
		; runner.dlist_node = runner.dlist_node->next)
	{
		check = is_match(runner.dlist_node->data, element_to_find);
		if (check)
		{
			to = runner;
		}
	}

	return to;
}

/*****************************************************************************/

int DListForEach(
    dlist_iter_t from,
    dlist_iter_t to,
    int (*action)(void *data, void *param),
    void *param
    )
{
	dlist_iter_t runner;
	int check = 0;

	runner.dlist_node = from.dlist_node;
	
	for (; runner.dlist_node != to.dlist_node 
		; runner.dlist_node = runner.dlist_node->next)
	{
		check = action(runner.dlist_node->data, param);
		if (check)
		{
			return check;
		}
	}

	return check;
}

/*****************************************************************************/

int DListMultiFind(
    dlist_iter_t from,
    dlist_iter_t to,
    int(*is_match)(const void *data, const void *param),
    const void *param,
    dlist_t *output_list
    )
{
	dlist_iter_t runner, check, list;

	assert(NULL != output_list);

	runner.dlist_node = from.dlist_node;
	list = DListEnd(output_list);
	
	for (; runner.dlist_node != to.dlist_node
		; runner.dlist_node = runner.dlist_node->next)
	{
		if (is_match(runner.dlist_node->data, param))
		{
			check = DListInsert(list, (void *)param);
			if (NULL == check.dlist_node)
			{
				return -1;
			}
		}
	}

	return DListIsEmpty(output_list);
}

/*****************************************************************************/

dlist_iter_t DListPushFront(dlist_t *dlist, void *data)
{
	assert(NULL != dlist);

	return DListInsert(DListBegin(dlist), data);
}

/*****************************************************************************/

dlist_iter_t DListPushBack(dlist_t *dlist, void *data)
{
	assert(NULL != dlist);

	return DListInsert(DListEnd(dlist), data);
}

/*****************************************************************************/

void *DListPopFront(dlist_t *dlist)
{
	void *data =  dlist->head.next->data;

	assert(NULL != dlist);
	
	DListRemove(DListBegin(dlist));

	return data;
}

/*****************************************************************************/

void *DListPopBack(dlist_t *dlist)
{
	void *data =  dlist->tail.prev->data;

	assert(NULL != dlist);
	
	DListRemove(DListPrev(DListEnd(dlist)));
	
	return data;
}

/*****************************************************************************/

dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
	dlist_node_t *before_to = to.dlist_node->prev;

	assert(NULL != where.dlist_node->prev);
	
	from.dlist_node->prev->next = to.dlist_node;
	to.dlist_node->prev = from.dlist_node->prev;

	before_to->next = where.dlist_node;
	from.dlist_node->prev = where.dlist_node->prev;

	where.dlist_node->prev->next = from.dlist_node;
	where.dlist_node->prev = before_to;
	
	return where;
}

/*****************************************************************************/

/* fix all functions to be simpler and use functions inside of functions */

