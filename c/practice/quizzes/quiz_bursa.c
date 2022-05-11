#include <stdio.h>

struct bursa
{
	int buy;
	int sell;
	int profit;
};

static struct bursa a;

void Bursa(int array[], int size)
{
	int i = 0;

	int b = 0, s = 0, p = 0;

	for (; i < size; i++)
	{
		if (array[i] < array[b])
		{
			b = i;
		}

		if (array[i] > array[s])
		{
			s = i;
		}
	}

	p = array[s] - array[b];

	a.buy = b;

	a.sell = s;

	a.profit = p;
}

int main(void)
{
	
	int array[5] = {1,3,7,5,2};

	Bursa(array, 5);

	printf("Buy index: %d\nSell index: %d\nProfit: %d\n", a.buy, a.sell, a.profit);

	return 0;
}
