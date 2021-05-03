/*****************************************************************************
Title: quiz_rotations 
Description: learn quiz_rotations
******************************************************************************/

#include <stdio.h> /* printf */

/*****************************************************************************/

int FindRotations(int arr[], size_t size)
{
	size_t i = 1;
	size_t count = 0;

	for (; i < size && arr[i] > arr[i - 1]; ++i)
	{}

	for (; i < size; ++i, ++count)
	{}

	return count; 

}

int main(void)
{
	int arr[] = {7,8,11,1,4,5};

	printf("rotations: %d\n", FindRotations(arr, 6));

	return 0;
}

/*****************************************************************************/

