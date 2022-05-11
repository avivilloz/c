#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct heap
{
	int *arr;
	size_t size;
	int (*is_before)(int, int);
} heap_t;

static size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);
	return heap->size;
}

static size_t HeapIsEmpty(const heap_t *heap)
{
	return 0 == heap->size;
}

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
			heap->arr[GetLeftChild(i)], 
			heap->arr[GetRightChild(i)]))
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
	int temp = heap->arr[i];
	heap->arr[i] = heap->arr[j];
	heap->arr[j] = temp;
}

static void HeapifyUp(heap_t *heap, size_t element_to_heapify)
{
	size_t element_to_compare = GetParent(element_to_heapify);

	for (; 0 != element_to_heapify && !heap->is_before(
		heap->arr[element_to_compare], 
		heap->arr[element_to_heapify])
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
		heap->arr[element_to_compare], 
		heap->arr[element_to_heapify])
		; element_to_heapify = element_to_compare, 
		element_to_compare = GetBiggestChild(heap, element_to_heapify))
	{
		Swap(heap, element_to_heapify, element_to_compare);
	}
}

static int IsBefore(int lhs, int rhs)
{
	return (lhs > rhs);
}

static heap_t *HeapCreate(size_t capacity)
{
	heap_t *new_heap = NULL;

	new_heap = (heap_t *)malloc(sizeof(heap_t));
	if (NULL == new_heap)
	{
		return NULL;
	}

	new_heap->arr = (int *)malloc(capacity * sizeof(int));
	if (NULL == new_heap->arr)
	{
		free(new_heap);
		new_heap = NULL;
		return NULL;
	}

	new_heap->size = 0;
	new_heap->is_before = IsBefore;

	return new_heap;
}

static void HeapPush(heap_t *heap, int num)
{
	size_t last_element = 0;

	assert(NULL != heap);
	
	heap->arr[heap->size] = num;

	++heap->size;

	last_element = HeapSize(heap) - 1;

	HeapifyUp(heap, last_element);
}

static void HeapPop(heap_t *heap)
{ 
	size_t last_element = 0;

	assert(NULL != heap);
 
	if (!HeapIsEmpty(heap))
	{
		last_element = HeapSize(heap) - 1;

		Swap(heap, 0, last_element);

		--heap->size;

		HeapifyDown(heap, 0);
	}
}

int HeapSort(int arr[], size_t size)
{
	size_t i = 0;
	heap_t *heap = HeapCreate(size);
	if (NULL == heap)
	{
		return 1;
	}

	for (; i < size; ++i)
	{
		HeapPush(heap, arr[i]);
	}

	for (i = 0; i < size; ++i)
	{
		HeapPop(heap);
	}

	memcpy(arr, heap->arr, size * sizeof(int));

	free(heap->arr);
	heap->arr = NULL;
	free(heap);
	heap = NULL;

	return 0;
}
