/****************************************************************************
Title: Sorts - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Igor
Description: Sorts API
*****************************************************************************/

#include <stdlib.h>	/* malloc, free */
#include <string.h>	/* memmove */
#include <assert.h>	/* assert */
#include "sorts.h"	/* api */

enum {NOT_FOUND = -1};
enum {SUCCESS, FAILURE};

/*************************** MAIN STATIC FUNCTIONS ***************************/

static void CountingSortRaw(
	const int *arr,
	size_t size,
	int min, int max,
	size_t *histograms,
	int *result
);

/***********************************/

static void RadixCountingSort(
	int *arr, 
	size_t size,  
	unsigned int bits_in_chunk, 
	size_t *histograms, 
	int *result
);
static void ResetHistograms(size_t *histograms, size_t size);

/***********************************/

static ssize_t RecursiveBinarySearchRaw(
	int arr[], 
	size_t left_index, 
	size_t right_index, 
	int data
);

/***********************************/

static void MergeSortRec(int arr[], size_t size, int temp_arr[]);
static void Merge(int arr[], size_t size, int temp_arr[]);

/***********************************/

static size_t InsertPivot(
	void *base, 
	size_t nmemb, 
	size_t size,
	int (*compar)(const void *, const void *)
);

/****
    void BFS(int s);  ******************** GENERAL STATIC FUNCTIONS ***************************/

static void Swap(int arr[], size_t i, size_t j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

static void SwapVoid(size_t size, void *a, void *b)
{
	size_t i = 0;
	unsigned char temp = '\0';
	unsigned char *buffer1 = (unsigned char *)a;
	unsigned char *buffer2 = (unsigned char *)b;

	for (; i < size; ++i)
	{
		temp  = buffer1[i];
		buffer1[i] = buffer2[i];
		buffer2[i] = temp;
	}
}

static void SwapIndexes(size_t *i, size_t *j)
{
	size_t temp = *i;
	*i = *j;
	*j = temp;
}

/******************************* FUNCTIONS ***********************************/

void BubbleSort(int arr[], size_t size)
{
	size_t i = 0;

	for (; size > 0; --size)
	{
		for (i = 0; i < size - 1; ++i)
		{			
			if (arr[i] > arr[i + 1])
			{
				Swap(arr, i, i + 1);
			}
		}
	}
}

/*****************************************************************************/

void BubbleSortOptimized(int arr[], size_t size)
{
	size_t i = 0;
	int exit = 0;

	for (; size > 0 && !exit; --size)
	{
		for (i = 0, exit = 1; i < size - 1; ++i)
		{			
			if (arr[i] > arr[i + 1])
			{
				exit = 0;
				Swap(arr, i, i + 1);
			}
		}
	}
}

/*****************************************************************************/

void SelectionSort(int arr[], size_t size)
{
	size_t i = 0, j = 0;

	for (; i < size; ++i)
	{
		int min = arr[i];
		size_t min_index = i;
		for (j = i; j < size; ++j)
		{
			if (arr[j] < min)
			{
				min = arr[j];
				min_index = j;
			}
		}
		Swap(arr, i, min_index);
	}
}

/*****************************************************************************/

void InsertionSort(int arr[], size_t size)
{
	size_t i = 0;
	int j = 0;	/* "int" because we check if is equal to zero */
	
	for (; i < size; ++i)
	{
		int temp = arr[i];
		size_t temp_index = i;
		for (j = i; j >= 0; --j)
		{
			if (temp < arr[j])
			{
				Swap(arr, j, temp_index);
				temp_index = j;
			}
		}
	}
}


/*
Nour's solution:
void InsertionSort(int arr[], size_t size)
{
	size_t i = 1;
	
	for (; i < size; ++i)
	{
		int temp = arr[i];
		int j = i - 1;	
		for (; j >= 0 && temp < arr[j]; --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
	}
}
*/

/*****************************************************************************/

int CountingSort(int *arr, size_t size, int min, int max)
{
	int *result = NULL;
	size_t *histograms = NULL;

	assert(NULL != arr);

	result = malloc(size * sizeof(int));
	if (NULL == result)
	{
		return 1;
	}

	histograms = calloc((max - min) + 1, sizeof(size_t));
	if (NULL == histograms)
	{
		free(result);
		result = NULL;
		return 1;
	}
	
	CountingSortRaw(arr, size, min, max, histograms, result);
	memmove(arr, result, size * sizeof(int));

	free(result);
	result = NULL;

	free(histograms);
	histograms = NULL;

	return 0;
}

static void CountingSortRaw(
	const int *arr,
	size_t size,
	int min, int max,
	size_t *histograms,
	int *result
)
{
	size_t i = 0, histograms_size = max - min;
	size_t temp = 0, temp2 = 0;

	for (; i < size; ++i)
	{
		++histograms[arr[i] - min];
	}
	
	temp = histograms[0];
	histograms[0] = 0;
	for (i = 0; i < histograms_size; ++i)
	{
		temp2 = histograms[i + 1];
		histograms[i + 1] = histograms[i] + temp;
		temp = temp2;
	}

	for (i = 0; i < size; ++i)
	{
		result[histograms[arr[i] - min]] = arr[i];
		++histograms[arr[i] - min];
	}
}

/*****************************************************************************/

int RadixSort(int *arr, size_t size, unsigned int bits_in_chunk)
{
	size_t *histograms = NULL;
	int *result = NULL;

	assert(!((bits_in_chunk - 1) & bits_in_chunk) && (32 >= bits_in_chunk));

	result = malloc(size * sizeof(int));
	if (NULL == result)
	{
		return 1;
	}

	histograms = malloc((1 << bits_in_chunk) * sizeof(size_t));
	if (NULL == histograms)
	{
		free(result);
		result = NULL;
		return 1;
	}

	RadixCountingSort(arr, size, bits_in_chunk, histograms, result);

	free(result);
	result = NULL;

	free(histograms);
	histograms = NULL;

	return 0;
}

static void RadixCountingSort(
	int *arr, 
	size_t size,  
	unsigned int bits_in_chunk, 
	size_t *histograms, 
	int *result
)
{
	size_t i = 0, j = 0, histograms_size = 1 << bits_in_chunk;
	unsigned int mask = histograms_size - 1;
	size_t temp = 0, temp2 = 0;

	for (; i < 32; i += bits_in_chunk, mask <<= bits_in_chunk)
	{
		ResetHistograms(histograms, histograms_size);
	
		for (j = 0; j < size; ++j)
		{
			++histograms[(arr[j] & mask) >> i];
		}

		temp = histograms[0];
		histograms[0] = 0;
		for (j = 0; j < histograms_size - 1; ++j)
		{
			temp2 = histograms[j + 1];
			histograms[j + 1] = histograms[j] + temp;
			temp = temp2;
		}
 
		for (j = 0; j < size; ++j)
		{
			result[histograms[(arr[j] & mask) >> i]] = arr[j];
			++histograms[(arr[j] & mask) >> i];
		}

		memmove(arr, result, size * sizeof(int));
	}
}

static void ResetHistograms(size_t *histograms, size_t size)
{
	size_t i = 0;

	for (; i < size; ++i)
	{
		histograms[i] = 0;
	}
}	

/*****************************************************************************/

ssize_t BinarySearch(int arr[], size_t size, int data)
{
	ssize_t left_index = 0, right_index = size - 1;
	ssize_t middle = ((right_index - left_index + 1) / 2) + left_index;
	
	while (right_index >= left_index)
	{
		if (arr[middle] < data)
		{
			left_index = middle + 1;
		}
		else if (arr[middle] > data)
		{
			right_index = middle - 1;
		}
		else
		{
			return middle;
		}
	
		middle = ((right_index - left_index + 1) / 2) + left_index;
	}

	return NOT_FOUND;
}

/*****************************************************************************/

ssize_t RecursiveBinarySearch(int arr[], size_t size, int data)
{
	size_t left_index = 0, right_index = size - 1;

	return RecursiveBinarySearchRaw(arr, left_index, right_index, data);
}

static ssize_t RecursiveBinarySearchRaw(
	int arr[], 
	size_t left_index, 
	size_t right_index, 
	int data
)
{
	size_t middle = ((right_index - left_index + 1) / 2) + left_index;
    
	if (arr[middle] == data)
	{
		return middle;
	}
	else if (right_index <= left_index)
	{
		return NOT_FOUND;
	}
	else
	{
		if (arr[middle] < data)
		{
			return RecursiveBinarySearchRaw(arr, 
							middle + 1, 
							right_index, 
							data);
		}
		else
		{
			return RecursiveBinarySearchRaw(arr, 
							left_index, 
							middle - 1, 
							data);
		}
	}

}

/*****************************************************************************/

int MergeSort(int arr[], size_t size)
{
	int *buffer = (int *)malloc(size * sizeof(int));
	if (NULL == buffer)	
	{
		return FAILURE;
	}

	MergeSortRec(arr, size, buffer);

	free(buffer);
	buffer = NULL;

	return SUCCESS;
}

static void MergeSortRec(int arr[], size_t size, int buffer[])
{
	if (1 < size)
	{
		size_t start_h
    void BFS(int s);  alf = size / 2, end_half = start_half + (size % 2);

		MergeSortRec(arr, start_half, buffer);
		MergeSortRec(arr + start_half, end_half, buffer);

		Merge(arr, size, buffer);
	}
}

static void Merge(int arr[], size_t size, int buffer[])
{
	size_t half = size / 2;
	size_t i = 0, j = half, k = 0;

	for (; k < size; ++k)
	{
		if (j == size || (i != half && arr[i] < arr[j]))
		{
			buffer[k] = arr[i];
			++i;
		}
		else
		{
			buffer[k] = arr[j];
			++j;
		}
	}

	memmove(arr, buffer, size * sizeof(int));
}

/*****************************************************************************/

void QuickSort(
	void *base, 
	size_t nmemb, 
	size_t size,
	int (*compar)(const void *, const void *)
)
{
	size_t first_half_size = 0, second_half_size = 0;
	void *second_half = NULL;

	if (nmemb > 1)
	{
		first_half_size = InsertPivot(base, nmemb, size, compar);
		second_half_size = nmemb - (first_half_size + 1);
		second_half = (char *)base + ((first_half_size + 1) * size);

		QuickSort(base, first_half_size, size, compar);
		QuickSort(second_half, second_half_size, size, compar);
	}
}

static size_t InsertPivot(
	void *base, 
	size_t nmemb, 
	size_t size,
	int (*compar)(const void *, const void *)
)
{
	size_t pivot = 0, i = nmemb - 1;
	
	while (i != pivot)
	{
		char *runner1 = (char *)base + (pivot * size);
		char *runner2 = (char *)base + (i * size);
		if (pivot < i)
		{
			if (compar(runner1, runner2) > 0)
			{
				SwapVoid(size, runner1, runner2);
				SwapIndexes(&pivot, &i);
				i += 2;
			}
			--i;
		}
		else
		{
			if (compar(runner1, runner2) < 0)
			{
				SwapVoid(size, runner1, runner2);
				SwapIndexes(&pivot, &i);
				i -= 2;
			}
			++i;
		}
	}

	return pivot;
}

/*****************************************************************************/
