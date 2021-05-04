/****************************************************************************
Title: Sorts
Author: Aviv Illoz
Description: Sorts API
*****************************************************************************/

#ifndef __SORTS_ILRD_OL91__
#define __SORTS_ILRD_OL91__

#include <sys/types.h>	/* ssize_t, size_t */

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

void BubbleSort(int array[], size_t size);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

void BubbleSortOptimized(int array[], size_t size);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

void SelectionSort(int array[], size_t size);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

void InsertionSort(int array[], size_t size);

/************************** NON-COMPARISON SORTS *****************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

int CountingSort(int *arr, size_t size, int min, int max);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

int RadixSort(int *arr, size_t size, unsigned int bits_in_chunk);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

ssize_t BinarySearch(int arr[], size_t size, int data);
ssize_t RecursiveBinarySearch(int arr[], size_t size, int data);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

int MergeSort(int arr[], size_t size);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

void QuickSort(
	void *base, 
	size_t nmemb, 
	size_t size,
	int (*compar)(const void *, const void *)
);

int HeapSort(int arr[], size_t size);

#endif /*__SORTS_ILRD_OL91__*/

