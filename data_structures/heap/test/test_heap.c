/****************************************************************************
Title: Heap - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Igor
Description: Heap Test API
*****************************************************************************/

#include <stdio.h>		/* printf */
#include <unistd.h>		/* sleep */

#include "heap.h"		/* api */
#include "pq_heap.h"		/* api */
#include "scheduler_heap.h"	/* api */

#define expect(x)	if (!(x))\
			{\
				return TEST_FAIL;\
			}\

#define RUN_TEST(x)	if (TEST_FAIL == (x))\
			{\
				printf("%s: \33[5;1;31mFAILURE\33[0m\n", #x);\
				success = FALSE;\
			}\
			else\
			{\
				printf("%s: \33[5;1;32;1mSUCCESS\33[0m\n", #x);\
			}

/*****************************************************************************/

enum {FALSE, TRUE};
typedef enum {TEST_PASS, TEST_FAIL} test_status_t;

/********************************* TESTS *************************************/

static int IsBefore(const void *lhs, const void *rhs)
{
	return (*(int *)lhs > *(int *)rhs);
}

static test_status_t HeapCreateDestroyTest(void)
{
	heap_t *heap = HeapCreate(IsBefore);
	if (NULL == heap)
	{
		return TEST_FAIL;
	}
	
	HeapDestroy(heap);

	return TEST_PASS;
}

#define ARR_SIZE 10

static test_status_t HeapPushPeekPopTest(void)
{
	int arr[ARR_SIZE] = {4,7,1,6,3,8,0,2,9,5};
	heap_t *heap = HeapCreate(IsBefore);
	if (NULL == heap)
	{
		return TEST_FAIL;
	}

	expect(0 == HeapPush(heap, &arr[0]));
	expect(4 == *(int *)HeapPeek(heap));	

	expect(0 == HeapPush(heap, &arr[1]));
	expect(7 == *(int *)HeapPeek(heap));	
	
	expect(0 == HeapPush(heap, &arr[2]));
	expect(7 == *(int *)HeapPeek(heap));	
	
	expect(0 == HeapPush(heap, &arr[3]));
	expect(7 == *(int *)HeapPeek(heap));	
	
	expect(0 == HeapPush(heap, &arr[4]));
	expect(7 == *(int *)HeapPeek(heap));	
	
	expect(0 == HeapPush(heap, &arr[5]));
	expect(8 == *(int *)HeapPeek(heap));	
	
	expect(0 == HeapPush(heap, &arr[6]));
	expect(8 == *(int *)HeapPeek(heap));	
	
	expect(0 == HeapPush(heap, &arr[7]));
	expect(8 == *(int *)HeapPeek(heap));	
	
	expect(0 == HeapPush(heap, &arr[8]));
	expect(9 == *(int *)HeapPeek(heap));	
	
	expect(0 == HeapPush(heap, &arr[9]));
	expect(9 == *(int *)HeapPeek(heap));	
		
	HeapPop(heap);
	expect(8 == *(int *)HeapPeek(heap));

	HeapPop(heap);
	expect(7 == *(int *)HeapPeek(heap));

	HeapPop(heap);
	expect(6 == *(int *)HeapPeek(heap));

	HeapPop(heap);
	expect(5 == *(int *)HeapPeek(heap));

	HeapPop(heap);
	expect(4 == *(int *)HeapPeek(heap));

	HeapPop(heap);
	expect(3 == *(int *)HeapPeek(heap));

	HeapPop(heap);
	expect(2 == *(int *)HeapPeek(heap));

	HeapPop(heap);
	expect(1 == *(int *)HeapPeek(heap));

	HeapPop(heap);
	expect(0 == *(int *)HeapPeek(heap));

	HeapPop(heap);
	expect(NULL == HeapPeek(heap));

	HeapDestroy(heap);

	return TEST_PASS;	
}

static test_status_t HeapIsEmptySizeTest(void)
{
	int arr[ARR_SIZE] = {4,7,1,6,3,8,0,2,9,5};
	heap_t *heap = HeapCreate(IsBefore);
	if (NULL == heap)
	{
		return TEST_FAIL;
	}

	expect(1 == HeapIsEmpty(heap));
	expect(0 == HeapSize(heap));

	expect(0 == HeapPush(heap, &arr[0]));
	expect(4 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(1 == HeapSize(heap));

	expect(0 == HeapPush(heap, &arr[1]));
	expect(7 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(2 == HeapSize(heap));

	expect(0 == HeapPush(heap, &arr[2]));
	expect(7 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(3 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[3]));
	expect(7 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(4 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[4]));
	expect(7 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(5 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[5]));
	expect(8 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(6 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[6]));
	expect(8 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(7 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[7]));
	expect(8 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(8 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[8]));
	expect(9 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(9 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[9]));
	expect(9 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(10 == HeapSize(heap));

	HeapPop(heap);
	expect(0 == HeapIsEmpty(heap));
	expect(9 == HeapSize(heap));

	HeapPop(heap);	
	expect(0 == HeapIsEmpty(heap));
	expect(8 == HeapSize(heap));

	HeapPop(heap);	
	expect(0 == HeapIsEmpty(heap));
	expect(7 == HeapSize(heap));
	
	HeapPop(heap);
	expect(0 == HeapIsEmpty(heap));
	expect(6 == HeapSize(heap));

	HeapPop(heap);
	expect(0 == HeapIsEmpty(heap));
	expect(5 == HeapSize(heap));

	HeapPop(heap);	
	expect(0 == HeapIsEmpty(heap));
	expect(4 == HeapSize(heap));

	HeapPop(heap);	
	expect(0 == HeapIsEmpty(heap));
	expect(3 == HeapSize(heap));

	HeapPop(heap);	
	expect(0 == HeapIsEmpty(heap));
	expect(2 == HeapSize(heap));

	HeapPop(heap);
	expect(0 == HeapIsEmpty(heap));
	expect(1 == HeapSize(heap));

	HeapPop(heap);
	expect(1 == HeapIsEmpty(heap));
	expect(0 == HeapSize(heap));

	HeapDestroy(heap);

	return TEST_PASS;
}

static int IsMatch(const void *lhs, const void *rhs)
{
	return (*(int *)lhs  == *(int *)rhs);
}

static test_status_t HeapRemoveTest(void)
{
	int arr[ARR_SIZE] = {4,7,1,6,3,8,0,2,9,5};
	heap_t *heap = HeapCreate(IsBefore);
	if (NULL == heap)
	{
		return TEST_FAIL;
	}

	expect(1 == HeapIsEmpty(heap));
	expect(0 == HeapSize(heap));

	expect(0 == HeapPush(heap, &arr[0]));
	expect(4 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(1 == HeapSize(heap));

	expect(0 == HeapPush(heap, &arr[1]));
	expect(7 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(2 == HeapSize(heap));

	expect(0 == HeapPush(heap, &arr[2]));
	expect(7 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(3 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[3]));
	expect(7 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(4 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[4]));
	expect(7 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(5 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[5]));
	expect(8 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(6 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[6]));
	expect(8 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(7 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[7]));
	expect(8 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(8 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[8]));
	expect(9 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(9 == HeapSize(heap));
	
	expect(0 == HeapPush(heap, &arr[9]));
	expect(9 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(10 == HeapSize(heap));

	expect(4 == *(int *)HeapRemove(heap, IsMatch, &arr[0]));	
	expect(0 == HeapIsEmpty(heap));
	expect(9 == HeapSize(heap));

	expect(NULL == HeapRemove(heap, IsMatch, &arr[0]));

	expect(7 == *(int *)HeapRemove(heap, IsMatch, &arr[1]));	
	expect(0 == HeapIsEmpty(heap));
	expect(8 == HeapSize(heap));

	expect(NULL == HeapRemove(heap, IsMatch, &arr[1]));

	expect(1 == *(int *)HeapRemove(heap, IsMatch, &arr[2]));	
	expect(0 == HeapIsEmpty(heap));
	expect(7 == HeapSize(heap));

	expect(NULL == HeapRemove(heap, IsMatch, &arr[2]));

	expect(6 == *(int *)HeapRemove(heap, IsMatch, &arr[3]));	
	expect(0 == HeapIsEmpty(heap));
	expect(6 == HeapSize(heap));

	expect(NULL == HeapRemove(heap, IsMatch, &arr[3]));

	expect(3 == *(int *)HeapRemove(heap, IsMatch, &arr[4]));	
	expect(0 == HeapIsEmpty(heap));
	expect(5 == HeapSize(heap));

	expect(NULL == HeapRemove(heap, IsMatch, &arr[4]));
	
	expect(8 == *(int *)HeapRemove(heap, IsMatch, &arr[5]));	
	expect(0 == HeapIsEmpty(heap));
	expect(4 == HeapSize(heap));

	expect(NULL == HeapRemove(heap, IsMatch, &arr[5]));

	expect(0 == *(int *)HeapRemove(heap, IsMatch, &arr[6]));	
	expect(0 == HeapIsEmpty(heap));
	expect(3 == HeapSize(heap));

	expect(NULL == HeapRemove(heap, IsMatch, &arr[6]));

	expect(2 == *(int *)HeapRemove(heap, IsMatch, &arr[7]));	
	expect(0 == HeapIsEmpty(heap));
	expect(2 == HeapSize(heap));

	expect(NULL == HeapRemove(heap, IsMatch, &arr[7]));

	expect(9 == *(int *)HeapRemove(heap, IsMatch, &arr[8]));
	expect(5 == *(int *)HeapPeek(heap));	
	expect(0 == HeapIsEmpty(heap));
	expect(1 == HeapSize(heap));

	expect(NULL == HeapRemove(heap, IsMatch, &arr[8]));

	expect(5 == *(int *)HeapRemove(heap, IsMatch, &arr[9]));	
	expect(1 == HeapIsEmpty(heap));
	expect(0 == HeapSize(heap));

	expect(NULL == HeapRemove(heap, IsMatch, &arr[9]));

	HeapDestroy(heap);

	return TEST_PASS;
}

/*****************************************************************************/

static int IsAfter(const void *lhs, const void *rhs)
{
	return (*(int *)rhs > *(int *)lhs);
}

static test_status_t PQCreateDestroyTest(void)
{
	pq_t *pq = PQCreate(IsAfter);
	if (NULL == pq)
	{
		return TEST_FAIL;
	}

	PQDestroy(pq);

	return TEST_PASS;
}

static test_status_t PQEnqueueFrontDequeueTest(void)
{
	int arr[ARR_SIZE] = {4,7,1,6,3,8,0,2,9,5};
	pq_t *pq = PQCreate(IsAfter);
	if (NULL == pq)
	{
		return TEST_FAIL;
	}

	expect(0 == PQEnqueue(pq, &arr[0]));
	expect(4 == *(int *)PQFront(pq));

	expect(0 == PQEnqueue(pq, &arr[1]));
	expect(4 == *(int *)PQFront(pq));

	expect(0 == PQEnqueue(pq, &arr[2]));
	expect(1 == *(int *)PQFront(pq));

	expect(0 == PQEnqueue(pq, &arr[3]));
	expect(1 == *(int *)PQFront(pq));

	expect(0 == PQEnqueue(pq, &arr[4]));
	expect(1 == *(int *)PQFront(pq));

	expect(0 == PQEnqueue(pq, &arr[5]));
	expect(1 == *(int *)PQFront(pq));

	expect(0 == PQEnqueue(pq, &arr[6]));
	expect(0 == *(int *)PQFront(pq));

	expect(0 == PQEnqueue(pq, &arr[7]));
	expect(0 == *(int *)PQFront(pq));

	expect(0 == PQEnqueue(pq, &arr[8]));
	expect(0 == *(int *)PQFront(pq));

	expect(0 == PQEnqueue(pq, &arr[9]));
	expect(0 == *(int *)PQFront(pq));

	expect(0 == *(int *)PQDequeue(pq));
	expect(1 == *(int *)PQDequeue(pq));
	expect(2 == *(int *)PQDequeue(pq));
	expect(3 == *(int *)PQDequeue(pq));
	expect(4 == *(int *)PQDequeue(pq));
	expect(5 == *(int *)PQDequeue(pq));
	expect(6 == *(int *)PQDequeue(pq));
	expect(7 == *(int *)PQDequeue(pq));
	expect(8 == *(int *)PQDequeue(pq));
	expect(9 == *(int *)PQDequeue(pq));
	expect(NULL == PQDequeue(pq));

	PQDestroy(pq);

	return TEST_PASS;
}

static test_status_t PQIsEmptySizeTest(void)
{
	int arr[ARR_SIZE] = {4,7,1,6,3,8,0,2,9,5};
	pq_t *pq = PQCreate(IsAfter);
	if (NULL == pq)
	{
		return TEST_FAIL;
	}

	expect(1 == PQIsEmpty(pq));
	expect(0 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[0]));
	expect(4 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(1 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[1]));
	expect(4 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(2 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[2]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(3 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[3]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(4 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[4]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(5 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[5]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(6 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[6]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(7 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[7]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(8 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[8]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(9 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[9]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(10 == PQSize(pq));


	expect(0 == *(int *)PQDequeue(pq));
	expect(0 == PQIsEmpty(pq));
	expect(9 == PQSize(pq));	

	expect(1 == *(int *)PQDequeue(pq));
	expect(0 == PQIsEmpty(pq));
	expect(8 == PQSize(pq));

	expect(2 == *(int *)PQDequeue(pq));
	expect(0 == PQIsEmpty(pq));
	expect(7 == PQSize(pq));

	expect(3 == *(int *)PQDequeue(pq));
	expect(0 == PQIsEmpty(pq));
	expect(6 == PQSize(pq));

	expect(4 == *(int *)PQDequeue(pq));
	expect(0 == PQIsEmpty(pq));
	expect(5 == PQSize(pq));

	expect(5 == *(int *)PQDequeue(pq));
	expect(0 == PQIsEmpty(pq));
	expect(4 == PQSize(pq));

	expect(6 == *(int *)PQDequeue(pq));
	expect(0 == PQIsEmpty(pq));
	expect(3 == PQSize(pq));

	expect(7 == *(int *)PQDequeue(pq));
	expect(0 == PQIsEmpty(pq));
	expect(2 == PQSize(pq));

	expect(8 == *(int *)PQDequeue(pq));
	expect(0 == PQIsEmpty(pq));
	expect(1 == PQSize(pq));

	expect(9 == *(int *)PQDequeue(pq));
	expect(1 == PQIsEmpty(pq));
	expect(0 == PQSize(pq));

	expect(NULL == PQDequeue(pq));
	expect(1 == PQIsEmpty(pq));
	expect(0 == PQSize(pq));

	PQDestroy(pq);

	return TEST_PASS;
}

static test_status_t PQEraseTest(void)
{
	int arr[ARR_SIZE] = {4,7,1,6,3,8,0,2,9,5};
	pq_t *pq = PQCreate(IsAfter);
	if (NULL == pq)
	{
		return TEST_FAIL;
	}

	expect(1 == PQIsEmpty(pq));
	expect(0 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[0]));
	expect(4 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(1 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[1]));
	expect(4 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(2 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[2]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(3 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[3]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(4 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[4]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(5 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[5]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(6 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[6]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(7 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[7]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(8 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[8]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(9 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[9]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(10 == PQSize(pq));

	expect(4 == *(int *)PQErase(pq, IsMatch, &arr[0]));
	expect(0 == PQIsEmpty(pq));
	expect(9 == PQSize(pq));	

	expect(NULL == PQErase(pq, IsMatch, &arr[0]));

	expect(7 == *(int *)PQErase(pq, IsMatch, &arr[1]));
	expect(0 == PQIsEmpty(pq));
	expect(8 == PQSize(pq));

	expect(NULL == PQErase(pq, IsMatch, &arr[1]));

	expect(1 == *(int *)PQErase(pq, IsMatch, &arr[2]));
	expect(0 == PQIsEmpty(pq));
	expect(7 == PQSize(pq));

	expect(NULL == PQErase(pq, IsMatch, &arr[2]));

	expect(6 == *(int *)PQErase(pq, IsMatch, &arr[3]));
	expect(0 == PQIsEmpty(pq));
	expect(6 == PQSize(pq));

	expect(NULL == PQErase(pq, IsMatch, &arr[3]));

	expect(3 == *(int *)PQErase(pq, IsMatch, &arr[4]));
	expect(0 == PQIsEmpty(pq));
	expect(5 == PQSize(pq));

	expect(NULL == PQErase(pq, IsMatch, &arr[4]));

	expect(8 == *(int *)PQErase(pq, IsMatch, &arr[5]));
	expect(0 == PQIsEmpty(pq));
	expect(4 == PQSize(pq));

	expect(NULL == PQErase(pq, IsMatch, &arr[5]));

	expect(0 == *(int *)PQErase(pq, IsMatch, &arr[6]));
	expect(0 == PQIsEmpty(pq));
	expect(3 == PQSize(pq));

	expect(NULL == PQErase(pq, IsMatch, &arr[6]));

	expect(2 == *(int *)PQErase(pq, IsMatch, &arr[7]));
	expect(0 == PQIsEmpty(pq));
	expect(2 == PQSize(pq));

	expect(NULL == PQErase(pq, IsMatch, &arr[7]));

	expect(9 == *(int *)PQErase(pq, IsMatch, &arr[8]));
	expect(0 == PQIsEmpty(pq));
	expect(1 == PQSize(pq));

	expect(NULL == PQErase(pq, IsMatch, &arr[8]));

	expect(5 == *(int *)PQErase(pq, IsMatch, &arr[9]));
	expect(1 == PQIsEmpty(pq));
	expect(0 == PQSize(pq));

	expect(NULL == PQErase(pq, IsMatch, &arr[9]));

	PQDestroy(pq);

	return TEST_PASS;
}

static test_status_t PQClearTest(void)
{
	int arr[ARR_SIZE] = {4,7,1,6,3,8,0,2,9,5};
	pq_t *pq = PQCreate(IsAfter);
	if (NULL == pq)
	{
		return TEST_FAIL;
	}

	expect(1 == PQIsEmpty(pq));
	expect(0 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[0]));
	expect(4 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(1 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[1]));
	expect(4 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(2 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[2]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(3 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[3]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(4 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[4]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(5 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[5]));
	expect(1 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(6 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[6]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(7 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[7]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(8 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[8]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(9 == PQSize(pq));

	expect(0 == PQEnqueue(pq, &arr[9]));
	expect(0 == *(int *)PQFront(pq));
	expect(0 == PQIsEmpty(pq));
	expect(10 == PQSize(pq));

	PQClear(pq);
	expect(1 == PQIsEmpty(pq));
	expect(0 == PQSize(pq));

	PQDestroy(pq);
	
	return TEST_PASS;
}

/*****************************************************************************/

enum repeat {ONCE = -1, FOREVER};

static int PrintIntParam(void *params)
{
	static int counter = 5;

	printf("Param = %d\n", *(int *)params);

	--counter;

	return (0 == counter);
}

static int AddTen(void *params)
{
	*(int *)params += 10;

	sleep(2);	

	return ONCE;
}

static int SubtractTen(void *params)
{
	*(int *)params -= 10;

	return ONCE;
}

static int MultiplyByTen(void *params)
{
	*(int *)params *= 10;

	return ONCE;
}

static int DivideByTen(void *params)
{
	*(int *)params /= 10;

	return ONCE;
}

static int Stop(void *params)
{
	SchedulerStop((scheduler_t *)params);
	
	return ONCE;
}

static test_status_t SchedulerTest(void)
{
	int params = 40;
	ilrd_uid_t uid_array[6];
	scheduler_t *scheduler = SchedulerCreate();
	if (NULL == scheduler)
	{
		return TEST_FAIL;
	}

	printf("****************** CREATED ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

	uid_array[0] = SchedulerAddTask(scheduler, PrintIntParam, &params, 0, 2);
	uid_array[1] = SchedulerAddTask(scheduler, AddTen, &params, 2, 0);
	uid_array[2] = SchedulerAddTask(scheduler, SubtractTen, &params, 4, 0);
	uid_array[3] = SchedulerAddTask(scheduler, MultiplyByTen, &params, 6, 0);
	uid_array[4] = SchedulerAddTask(scheduler, DivideByTen, &params, 8, 0);
	uid_array[5] = SchedulerAddTask(scheduler, DivideByTen, &params, 8, 0);

	printf("****************** INSERTED ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

	SchedulerCancel(scheduler, uid_array[5]);

	printf("****************** LAST CANCELED ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

	printf("****************** RUNNING FIRST TIME ***********************\n");

	printf("Run status: %d\n", SchedulerRun(scheduler));

/*****************************************************************************/

	uid_array[0] = SchedulerAddTask(scheduler, PrintIntParam, &params, 0, 2);
	uid_array[1] = SchedulerAddTask(scheduler, AddTen, &params, 2, 0);
	uid_array[2] = SchedulerAddTask(scheduler, SubtractTen, &params, 4, 0);
	uid_array[3] = SchedulerAddTask(scheduler, MultiplyByTen, &params, 6, 0);
	uid_array[4] = SchedulerAddTask(scheduler, DivideByTen, &params, 8, 0);

	printf("****************** INSERTED ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

	SchedulerClear(scheduler);

	printf("****************** CLEARED ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

/*****************************************************************************/

	uid_array[0] = SchedulerAddTask(scheduler, PrintIntParam, &params, 0, 2);
	uid_array[1] = SchedulerAddTask(scheduler, AddTen, &params, 2, 0);
	uid_array[2] = SchedulerAddTask(scheduler, SubtractTen, &params, 4, 0);
	uid_array[3] = SchedulerAddTask(scheduler, MultiplyByTen, &params, 6, 0);
	uid_array[4] = SchedulerAddTask(scheduler, DivideByTen, &params, 8, 0);
	uid_array[5] = SchedulerAddTask(scheduler, Stop, scheduler, 4, 0);

	printf("****************** INSERTED WITH STOP ***********************\n");

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));
 
	printf("****************** RUNNING AGAIN WITH STOP ***********************\n");

	printf("Run status: %d\n", SchedulerRun(scheduler));

	printf("Size: %lu\n", SchedulerSize(scheduler));
	printf("Empty? %d\n", SchedulerIsEmpty(scheduler));

/*****************************************************************************/
	
	printf("****************** DESTROYING ***********************\n");

	SchedulerDestroy(scheduler);

	return TEST_PASS;
}

/*****************************************************************************/

int main(void)
{
	int success = TRUE;

/*
*/
	RUN_TEST(HeapCreateDestroyTest());
	RUN_TEST(HeapPushPeekPopTest());
	RUN_TEST(HeapIsEmptySizeTest());
	RUN_TEST(HeapRemoveTest());
	RUN_TEST(PQCreateDestroyTest());
	RUN_TEST(PQEnqueueFrontDequeueTest());
	RUN_TEST(PQIsEmptySizeTest());
	RUN_TEST(PQEraseTest());
	RUN_TEST(PQClearTest());
/*
	RUN_TEST(SchedulerTest());
*/

	if (success)
	{
		printf("Test was a: \33[5;1;32;1mSUCCESS\33[0m\n");
	}
	else
	{
		printf("Test was a: \33[5;1;31mFAILURE\33[0m\n");
	}

	return 0;
}


