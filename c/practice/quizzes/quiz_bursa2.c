#include <stdio.h>

typedef struct bursa
{
	size_t buy;
	size_t sell;
	unsigned long profit;
} bursa_t;


/*bursa_t Bursa(unsigned long prices[], size_t size)
{
	bursa_t new_bursa;
	size_t i = 0, temp = 0;

	new_bursa.buy = i;
	new_bursa.sell = i;
	
	for (; i < size; ++i)
	{
		if (prices[i] > prices[new_bursa.sell])
		{
			new_bursa.sell = i;
		}

		if (prices[i] < prices[new_bursa.buy])
		{
			temp = i;
		}

		if (temp < new_bursa.sell) 
		{
			new_bursa.buy = temp;
		}
	}
	
	new_bursa.profit = prices[new_bursa.sell] - prices[new_bursa.buy];
	
	return new_bursa;
}*/

/* david's solution */
bursa_t Bursa(unsigned long prices[], size_t size)
{
	bursa_t new_bursa;
	size_t min = 0, max = 0;

	new_bursa.profit = 0;
	
	for (; max < size; ++max)
	{
		if (prices[max] <= prices[min])
		{
			min = max;
		}

		else if (prices[max] - prices[min] > new_bursa.profit)
		{
			new_bursa.buy = min;
			new_bursa.sell = max;
			new_bursa.profit = prices[max] - prices[min];
		}
	}
	
	return new_bursa;
}


int main(void)
{
	unsigned long prices[10] = {1,5,0,7,2,9,6,8,2,0};
	bursa_t bursa = Bursa(prices, 10);

	printf("%lu, %lu, %lu\n", bursa.buy, bursa.sell, bursa.profit);

	return 0;
}
