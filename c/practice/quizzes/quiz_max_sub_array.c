#include <stdio.h>
#define SIZE 8

void MaxSubArray(int a[], int size)
{
	int i = 0, j1 = 0, j2 = 0, k1 = 0, k2 = 0, sum1 = 0, sum2 = 0;

	for (; i < size; ++i)
	{
		if (a[i] >= 0)
		{
			j1 = i;

			j2 = i;

			sum1 = a[i];
		}

		while (j2 < size && a[i] >= 0)
		{
			if (sum1 >= sum2)
			{
				sum2 = sum1;

				k1 = j1;

				k2 = j2;
			}	
			
			++j2;

			sum1 += a[j2];
		}
	}

	printf("from index %d to index %d\n", k1, k2);
}

int main(void)
{
	int a[SIZE] = {-1, -2, 1, 2, 3, -3, 2, 3};

	MaxSubArray(a, SIZE);

	return 0;
}
