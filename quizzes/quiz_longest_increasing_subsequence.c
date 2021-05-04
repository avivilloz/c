/*****************************************************************************
Title: longest_increasing_subsequence 
Description: learn longest_increasing_subsequence
******************************************************************************/

#include <stdio.h> /* printf */

/*****************************************************************************/

int rec(int arr[], size_t size, size_t i, size_t j)
{
	size_t lis = 0;
	size_t temp_is = 0;

	for (; i < size; ++i)
	{
		for (; j < size; ++j)
		{
			if (arr[j] > arr[i])
			{
				temp_is = rec(arr, size, j, j + 1);
				if (temp_is > lis)
				{
					lis = temp_is;
				}
			}
		}
	}

	return 1 + lis;
}

int longest_increasing_subsequence(int arr[], size_t size)
{
	return rec(arr, size, 0, 1);
}

int main(void)
{
	int arr[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
	printf("%d\n", longest_increasing_subsequence(arr, 16));

	return 0;
}

/*****************************************************************************/

