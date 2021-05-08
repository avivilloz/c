#include <stdio.h>

/*I had to add two more parameters to the function, 1- because I couldn't return more than 1 answer from the function, as well as an array, so I had to pass an array (ans) with enough size for 2 numbers to the function to begin with. 2- The size of the first array, since I couldn't calculate its size inside of the function, because an array sent to a function becames a pointer.*/

int IsSumFound(int *srtdarr, int size, int sum, int *ans)
{
	int i = 0, j = 1;

	for (; i < size; i++)
	{
		if (i > 0)
		{
			j = 0;
		}
		for (; j < size; j++)
		{
			if (j == i)
			{
				j++;
			}
			
			if (srtdarr[i] + srtdarr[j] == sum)
			{
				ans [0] = i;
				ans[1] = j;
				return 1;
			} 
		}
	}

	return 0;
}

int main(void)
{
	int arr[5] = {1,2,3,4,5};

	int sum = 6;
	
	int ans[2];

	int i;

	printf("%d\n", IsSumFound(arr, 5, sum, ans));

	for (i = 0; i < 2; i++)
	{
		printf("%d\n", ans[i]);
	}

	return 0;
}
