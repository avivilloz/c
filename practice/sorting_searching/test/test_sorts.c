/****************************************************************************
Title: Sorts - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Igor
Description: Sorts Test API
*****************************************************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, rand, srand */
#include <string.h>	/* memmove */
#include <time.h>	/* time */

#include "sorts.h"	/* api */

#define expect(x)	if (!(x))\
			{\
				return TEST_FAIL;\
			}

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

enum {SUCCESS, FAILURE};
enum {FALSE, TRUE};
enum {TEST_PASS, TEST_FAIL};

/************************ COMPARISON SORTS TEST *****************************/

static int CmpInts(const void *a, const void *b) 
{
	return (*(int *)a - *(int *)b);
}

static void SortRun(int *array, size_t size, void (*sort_func)(int array[], size_t size))
{
	clock_t start = clock();
	sort_func(array, size);
	printf("Clock Sort:  %lu\n", clock() - start);
}

static void QSortRun(int *qsort_array, size_t size)
{
	clock_t start = clock();
	qsort(qsort_array, size, sizeof(int), CmpInts);
	printf("Clock QSort: %lu\n", clock() - start);
}

static int SortAndCheck(void (*sort_func)(int array[], size_t size))
{
	int array[5000], qsort_array[5000];	
	size_t i = 0;
	
	srand(time(NULL));
	for (; i < 5000; i++) 
	{
		array[i] = rand() % 5000;
	}

	memmove(qsort_array, array, 5000 * sizeof(int));

	QSortRun(qsort_array, 5000);
	SortRun(array, 5000, sort_func);

	for (i = 0; i < 5000; ++i)
	{
		expect(array[i] == qsort_array[i]);
	}

	return TEST_PASS;
}

/************************ NON-COMPARISON SORTS TEST **************************/

static void CountingSortRun(int *array, size_t size, int min, int max)
{
	clock_t start = clock();
	CountingSort(array, size, min, max);
	printf("Clock CountingSort: %lu\n", clock() - start);
}

static void RadixSortRun(int *array, size_t size, unsigned int bits_in_chunk)
{
	clock_t start = clock();
	RadixSort(array, size, bits_in_chunk);
	printf("Clock RadixSort: %lu\n", clock() - start);
}

static int CountingSortCheck(void)
{
	int array[5000], qsort_array[5000], radix_array[5000];
	size_t i = 0;
	int min = 0, max = 0;
	
	srand(time(NULL));
	for (; i < 5000; i++) 
	{
		array[i] = rand() % 5000;
	}

	memmove(qsort_array, array, 5000 * sizeof(int));
	memmove(radix_array, qsort_array, 5000 * sizeof(int));

	QSortRun(qsort_array, 5000);

	min = qsort_array[0];
	max = qsort_array[4999];
	
	CountingSortRun(array, 5000, min, max);
	for (i = 0; i < 5000; ++i)
	{
		expect(array[i] == qsort_array[i]);
	}

	RadixSortRun(radix_array, 5000, 16);
	for (i = 0; i < 5000; ++i)
	{
		expect(radix_array[i] == qsort_array[i]);
	}

	return TEST_PASS;
}

/*****************************************************************************/

static int BinarySearchCheck(ssize_t (*sort_func)(int [], size_t, int))
{
	int arr[14] = {1,3,5,7,9,12,14,15,17,20,23,25,26,28};
	int arr2[2] = {2,6};
	int arr3[1] = {4};
	int arr4[3] = {2,6,8};

	expect(0 == sort_func(arr, 14, 1));
	expect(1 == sort_func(arr, 14, 3));
	expect(2 == sort_func(arr, 14, 5));
	expect(3 == sort_func(arr, 14, 7));
	expect(4 == sort_func(arr, 14, 9));
	expect(5 == sort_func(arr, 14, 12));
	expect(6 == sort_func(arr, 14, 14));
	expect(7 == sort_func(arr, 14, 15));
	expect(8 == sort_func(arr, 14, 17));
	expect(9 == sort_func(arr, 14, 20));
	expect(10 == sort_func(arr, 14, 23));
	expect(11 == sort_func(arr, 14, 25));
	expect(12 == sort_func(arr, 14, 26));
	expect(13 == sort_func(arr, 14, 28));
	expect(-1 == sort_func(arr, 14, 8));
	expect(-1 == sort_func(arr, 14, 30));
	expect(-1 == sort_func(arr, 14, -1));

	expect(1 == sort_func(arr2, 2, 6));
	expect(0 == sort_func(arr2, 2, 2));
	expect(-1 == sort_func(arr2, 2, 8));

	expect(0 == sort_func(arr3, 1, 4));
	expect(-1 == sort_func(arr3, 1, 5));

	expect(1 == sort_func(arr4, 3, 6));
	expect(0 == sort_func(arr4, 3, 2));
	expect(2 == sort_func(arr4, 3, 8));
	expect(-1 == sort_func(arr4, 3, 5));

	return TEST_PASS;
}

/*****************************************************************************/

/*static int MergeSortCheck(void)
{
	int arr[14] = {4,6,2,15,7,1,13,5,9,23,12,0,34,8};
	int qsort_array[14] = {4,6,2,15,7,1,13,5,9,23,12,0,34,8};
	size_t i = 0;

	expect(SUCCESS == MergeSort(arr, 14));

	qsort(qsort_array, 14, sizeof(int), CmpInts);

	for (i = 0; i < 14; ++i)
	{
		expect(arr[i] == qsort_array[i])
	}

	return TEST_PASS;
}*/

static int MergeSortCheck(void)
{
	int array[5000], qsort_array[5000];	
	size_t i = 0;
	clock_t start;	

	srand(time(NULL));
	for (; i < 5000; i++) 
	{
		array[i] = rand() % 5000;
	}

	memmove(qsort_array, array, 5000 * sizeof(int));

	QSortRun(qsort_array, 5000);
	
	start = clock();
	expect(SUCCESS == MergeSort(array, 5000));
	printf("Merge Sort:  %lu\n", clock() - start);

	for (i = 0; i < 5000; ++i)
	{
		expect(array[i] == qsort_array[i])
	}

	return TEST_PASS;
}

/*****************************************************************************/

/*
static int QuickSortCheck(void)
{
	int arr[14] = {4,6,2,15,7,1,13,5,9,23,12,0,34,8};
	int qsort_array[14] = {4,6,2,15,7,1,13,5,9,23,12,0,34,8};
	size_t i = 0;

	QuickSort(arr, 14, sizeof(int), CmpInts);

	qsort(qsort_array, 14, sizeof(int), CmpInts);

	for (i = 0; i < 14; ++i)
	{
		expect(arr[i] == qsort_array[i])
	}

	return TEST_PASS;
}
*/

static int QuickSortCheck(void)
{
	int array[5000], qsort_array[5000];	
	size_t i = 0;
	clock_t start;
	
	srand(time(NULL));
	for (; i < 5000; i++) 
	{
		array[i] = rand() % 5000;
	}

	memmove(qsort_array, array, 5000 * sizeof(int));

	QSortRun(qsort_array, 5000);

	start = clock();
	QuickSort(array, 5000, sizeof(int), CmpInts);
	printf("Quick Sort: %lu\n", clock() - start);

	for (i = 0; i < 5000; ++i)
	{
		expect(array[i] == qsort_array[i]);
	}

	return TEST_PASS;	
}

/*****************************************************************************/

static int HeapSortCheck(void)
{
	int array[5000], qsort_array[5000];	
	size_t i = 0;
	clock_t start;
	
	srand(time(NULL));
	for (; i < 5000; i++) 
	{
		array[i] = rand() % 5000;
	}

	memmove(qsort_array, array, 5000 * sizeof(int));

	QSortRun(qsort_array, 5000);

	start = clock();
	expect(0 == HeapSort(array, 5000));
	printf("Heap Sort: %lu\n", clock() - start);

	for (i = 0; i < 5000; ++i)
	{
		expect(array[i] == qsort_array[i]);
	}

	return TEST_PASS;
}

/*****************************************************************************/

int main(void)
{
	int success = TRUE;

	/*
	RUN_TEST(SortAndCheck(BubbleSort));
	RUN_TEST(SortAndCheck(BubbleSortOptimized));
	RUN_TEST(SortAndCheck(SelectionSort));
	RUN_TEST(SortAndCheck(InsertionSort));
	RUN_TEST(CountingSortCheck());
	RUN_TEST(BinarySearchCheck(BinarySearch));
	RUN_TEST(BinarySearchCheck(RecursiveBinarySearch));
	RUN_TEST(MergeSortCheck());
	RUN_TEST(QuickSortCheck());
	*/
	RUN_TEST(HeapSortCheck());	
	/*
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

