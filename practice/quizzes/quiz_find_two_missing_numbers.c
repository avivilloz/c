#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/* XOR solution */
/*
void FindTwoMissingNumbers(unsigned int a[], size_t size, size_t B)
{
	unsigned int x = 0, p = 0, q = 0; 
	size_t i = 0;

	for(; i < size; ++i)
	{
		x = x ^ a[i];
	}

	for(i = 1; i <= B; ++i)
	{
		x = x ^ i;
	}

	x = x &(~(x - 1));

	for(i = 0; i < size; ++i)
	{
		if((a[i] & x) == x)
		{
			p = p ^ a[i];
		}
		else
		{
			q = q ^ a[i];
		}   
	}

	for(i = 1; i <= B; ++i)
	{
		if((i & x) == x)
		{
			p = p ^ i;
		}
		else
		{
			q = q ^ i;
		}
	}

	printf("%d, %d\n", p, q);
}
*/

static int FindTwoMissingNumbers(unsigned int arr[], size_t size, unsigned int n)
{
	size_t i = 0;
	unsigned int *histogram = calloc(n, sizeof(int));
	if (NULL == histogram)
	{
		return 1;
	}

	for (; i < size; ++i)
	{
		histogram[arr[i] - 1] = arr[i]; 
	}

	for (i = 0; i < n; ++i)
	{
		if (0 == histogram[i])
		{
			printf("%d\n", (int)i + 1); 
		}	
	}

	return 0;
}

int main(void)
{
	int status = 0;
	unsigned int arr[3] = {4,2,1};

	status = FindTwoMissingNumbers(arr, 3, 5);
	if (1 == status)
	{
		return 1;
	}
	
	return 0;
}
