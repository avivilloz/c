/*******************************************************************************
* Title: Slist - Infinity Labs R&D 
* Group: Ol91
* Author: Aviv
* Reviewer: Miriam
* Description: Dynamic Linked List interface
********************************************************************************/

#include <stdlib.h>	/*malloc, free*/
#include <assert.h>	/*assert*/
#include "slist.h"	/*api*/

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

/*******************************************************************************/

slist_t *SListCreate(void)
{
	slist_t *return_slist = NULL;
	slist_iter_t dummy_node = NULL;
	
	return_slist = malloc(sizeof(slist_t));
	if (NULL == return_slist)
	{		
		return NULL;
	}

	dummy_node = malloc(sizeof(slist_node_t));
	if (NULL == dummy_node)
	{
		free(return_slist);
		return_slist = NULL;		
		return NULL;
	}

	/************ CREATE DUMMY NODE **************/

	dummy_node->data = return_slist;
	dummy_node->next = NULL;

	/************ POINT HEAD AND TAIL TO DUMMY NODE **************/

	return_slist->head = dummy_node;
	return_slist->tail = dummy_node;

	return return_slist;
}

/*******************************************************************************/

slist_iter_t SListBegin(const slist_t *slist)
{
	assert(NULL != slist);

	return slist->head;
}

/*******************************************************************************/

slist_iter_t SListEnd(const slist_t *slist)
{
	assert(NULL != slist);

	return slist->tail;
}

/*******************************************************************************/

slist_iter_t SListNext(slist_iter_t iter)
{
	assert(NULL != iter);

	return iter->next;
}

/*******************************************************************************/

int SListIsEmpty(const slist_t *iter)
{
	assert(NULL != iter);

	return (NULL == iter->head->next);
}

/*******************************************************************************/

size_t SListSize(const slist_t *slist)
{
	size_t size = 0;
	slist_iter_t runner = slist->head;

	assert(NULL != slist);

	while (NULL != runner->next)
	{
		runner = runner->next;
		++size;
	}

	return size;
}

/*******************************************************************************/

int SListIsSameIterator(const slist_iter_t lhs,const slist_iter_t rhs)
{
	assert(NULL != lhs && NULL != rhs);

	return (lhs == rhs);
}

/*******************************************************************************/

void *SListGetData(const slist_iter_t iter)
{
	assert(NULL != iter);

	return iter->data;
}

/*******************************************************************************/

void SListSetData(slist_iter_t iter, void *data)
{
	assert(NULL != iter);

	iter->data = data;
}

/*******************************************************************************/

slist_iter_t SListInsert(slist_iter_t iter, void *data)
{	
	slist_iter_t replace_node = NULL;

	assert(NULL != iter);

	replace_node = (slist_iter_t)malloc(sizeof(slist_node_t));
	if (NULL == replace_node)
	{
		return NULL;
	}

	/************ INSERT AND MOVE OLD NODE TO BE THE NEXT **************/

	replace_node->data = iter->data;
	replace_node->next = iter->next;
	iter->data = data;
	iter->next = replace_node;

	/*********** GET AND SET THE NEW TAIL ***************/

	if (NULL == replace_node->next)
	{
		((slist_t *)(replace_node->data))->tail = replace_node;
	}

	return iter;
}

/*******************************************************************************/

slist_iter_t SListRemove(slist_iter_t iter)
{
	slist_iter_t temp = iter->next;

	assert(NULL != iter);

	if (NULL == temp)
	{
		return NULL;
	}

	/************ SET ITER TO HAVE NEXT NODE'S VALUES **************/

	iter->data = temp->data;
	iter->next = temp->next;

	/*********** GET AND SET THE NEW TAIL ***************/

	if (NULL == iter->next)
	{
		((slist_t *)(iter->data))->tail = iter;
	}
	
	/************ REMOVE EXTRA NODE **************/

	free(temp);
	temp = NULL;

	return iter;
}

/*******************************************************************************/

void SListDestroy(slist_t *slist)
{
	slist_iter_t check = slist->head, temp = check;

	assert(NULL != slist);

	/************ FREE EACH NODE *****************/

	while (NULL != check)
	{
		check = check->next;
		free(temp);
		temp = check;
	}
	temp = NULL;

	/************ FREE WHOLE LIST ***************/

	free(slist);
	slist = NULL;
}

/*******************************************************************************/

slist_iter_t SListFind(
    	const slist_iter_t from,
    	const slist_iter_t to,
    	int (*is_match)(const void *data, const void *element_to_find),
    	const void *element_to_find
	)
{
	slist_iter_t return_iter = from;
	int check = 0;

	assert(NULL != to && NULL != from);

	while (return_iter != to->next)
	{
		check = is_match(return_iter->data, element_to_find);
		if (0 == check)
		{
			return return_iter;
		}
		return_iter = return_iter->next;
	}

	return NULL;
}

/*******************************************************************************/

int SListForEach(
   	const slist_iter_t from,
   	const slist_iter_t to,
    	int (*action)(void *data, void *param),
    	void *param
	)
{
	slist_iter_t runner = from;
	int check = 0;

	assert(NULL != to && NULL != from);

	for (; runner != to; runner = runner->next)
	{		
		check = action(runner->data, param);
		if (check)
		{
			return check;
		}
	}

	return check;
}

/*******************************************************************************/

void SListAppend(slist_t *dest, slist_t *src)
{
	/************* SETTING SRC TAIL DATA TO POINT TO DEST **************/

	src->tail->data = dest;

	/************* SETTING DEST TAIL TO SRC HEAD **************/

	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;

	/************* EMPTYING SRC **************/	

	src->head->data = src;
	src->head->next = NULL;
	src->tail = src->head;
}



