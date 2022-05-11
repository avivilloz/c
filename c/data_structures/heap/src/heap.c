/****************************************************************************
Title: Heap
Author: Aviv Illoz
Description: Heap API
*****************************************************************************/

#include <stdlib.h>	/* malloc */
#include <assert.h>	/* assert */
#include <sys/types.h>	/* ssize_t */

#include "heap.h"	/* api */

/*****************************************************************************/

struct heap
{
	vector_t *vector;
	is_before_t is_before;
};

/*****************************************************************************/

enum {SUCCESS, FAILURE};
enum {NOT_FOUND = -1};

/************************ STATIC FUNCTIONS ***********************************/

static ssize_t HeapFind(const heap_t *heap, is_match_t is_match, void *param);

/********************* GENERAL STATIC FUNCTIONS ******************************/

static size_t GetParent(size_t i)
{
	return i / 2;
}

static size_t GetLeftChild(size_t i)
{
	return 2 * i;
}

static size_t GetRightChild(size_t i)
{
	return 2 * i + 1;
}

static int HasChildren(heap_t *heap, size_t i)
{
	return (HeapSize(heap) > GetRightChild(i));
}

static int HasLeftChild(heap_t *heap, size_t i)
{
	return (HeapSize(heap) > GetLeftChild(i));
}

static size_t GetBiggestChild(heap_t *heap, size_t i)
{
	if (HasChildren(heap, i))
	{
		if (heap->is_before(
			VectorGetElement(heap->vector, GetLeftChild(i)), 
			VectorGetElement(heap->vector, GetRightChild(i))))
		{
			return GetLeftChild(i);
		}
	}
	else if (HasLeftChild(heap, i))
	{
		return GetLeftChild(i);
	}
	
	return GetRightChild(i);
}

static void Swap(heap_t *heap, size_t i, size_t j)
{
	void *i_data = VectorGetElement(heap->vector, i);
	void *j_data = VectorGetElement(heap->vector, j);

	VectorSetElement(heap->vector, i, j_data);
	VectorSetElement(heap->vector, j, i_data);
}

static void HeapifyUp(heap_t *heap, size_t element_to_heapify)
{
	size_t size = HeapSize(heap);
	size_t element_to_compare = GetParent(element_to_heapify);

	for (; element_to_heapify < size && 
		0 != element_to_heapify && !heap->is_before(
		VectorGetElement(heap->vector, element_to_compare), 
		VectorGetElement(heap->vector, element_to_heapify))
		; element_to_heapify = element_to_compare, 
		element_to_compare = GetParent(element_to_heapify))
	{
		Swap(heap, element_to_heapify, element_to_compare);
	}
}

static void HeapifyDown(heap_t *heap, size_t element_to_heapify)
{
	size_t size = HeapSize(heap);
	size_t element_to_compare = GetBiggestChild(heap, element_to_heapify);

	for (; element_to_compare < size && heap->is_before(
		VectorGetElement(heap->vector, element_to_compare), 
		VectorGetElement(heap->vector, element_to_heapify))
		; element_to_heapify = element_to_compare, 
		element_to_compare = GetBiggestChild(heap, element_to_heapify))
	{
		Swap(heap, element_to_heapify, element_to_compare);
	}
}

/******************************* FUNCTIONS ***********************************/

heap_t *HeapCreate(is_before_t is_before)
{
	heap_t *new_heap = NULL;

	assert(NULL != is_before);

	new_heap = (heap_t *)malloc(sizeof(heap_t));
	if (NULL == new_heap)
	{
		return NULL;
	}

	new_heap->vector = VectorCreate(3);
	if (NULL == new_heap->vector)
	{
		free(new_heap);
		new_heap = NULL;
		return NULL;
	}

	new_heap->is_before = is_before;

	return new_heap;
}

/*****************************************************************************/

void HeapDestroy(heap_t *heap)
{
	assert(NULL != heap);

	VectorDestroy(heap->vector);
	
	free(heap);
	heap = NULL;
}

/*****************************************************************************/

int HeapPush(heap_t *heap, void *data)
{
	size_t last_element = 0;

	assert(NULL != heap);
	
	if (FAILURE == VectorPushBack(heap->vector, data))
	{
		return FAILURE;
	}

	last_element = HeapSize(heap) - 1;

	HeapifyUp(heap, last_element);

	return SUCCESS;
}

/*****************************************************************************/

void HeapPop(heap_t *heap)
{ 
	size_t last_element = 0;

	assert(NULL != heap);
 
	if (!HeapIsEmpty(heap))
	{
		last_element = HeapSize(heap) - 1;

		Swap(heap, 0, last_element);

		VectorPopBack(heap->vector);

		HeapifyDown(heap, 0);
	}
}

/*****************************************************************************/

void *HeapPeek(heap_t *heap)
{
	assert(NULL != heap);

	if (HeapIsEmpty(heap))
	{
		return NULL;
	}

	return VectorGetElement(heap->vector, 0);
}

/*****************************************************************************/

size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);
	return VectorSize(heap->vector);
}

/*****************************************************************************/

int HeapIsEmpty(const heap_t *heap)
{
	assert(NULL != heap);
	return 0 == HeapSize(heap);
}

/*****************************************************************************/

void *HeapRemove(heap_t *heap, is_match_t is_match, void *param)
{
	ssize_t element_to_remove = 0;
	void *removed_element = NULL;
	size_t last_element = 0;
	void *last_element_data = NULL;

	assert(NULL != heap && NULL != is_match);

	element_to_remove = HeapFind(heap, is_match, param);
	
	if (NOT_FOUND == element_to_remove)
	{
		return NULL;
	}

	removed_element = VectorGetElement(heap->vector, element_to_remove);

	last_element = HeapSize(heap) - 1;
	last_element_data = VectorGetElement(heap->vector, last_element);

	VectorSetElement(heap->vector, element_to_remove, last_element_data);

	VectorPopBack(heap->vector);

	HeapifyDown(heap, element_to_remove);
	HeapifyUp(heap, element_to_remove);

	return removed_element;
}

static ssize_t HeapFind(const heap_t *heap, is_match_t is_match, void *param)
{
	size_t size = HeapSize(heap);
	size_t i = 0;

	for (; i < size; ++i)
	{
		if (is_match(VectorGetElement(heap->vector, i), param))
		{
			return i;
		}
	}

	return NOT_FOUND;
}

/*****************************************************************************/
