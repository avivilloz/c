/*****************************************************************************
* title: has three set on bits
* author: aviv illoz
* description: checks for numbers with 3 bits set on
******************************************************************************/

#include <stdio.h> /* printf */

void HasThreeSetOnBits(unsigned int n[], int size)
{	
	int i = 0, count = 0, check = 0;

	for (check = n[i]; i < size; i++, check = n[i], count = 0)
	{
		while (check)
		{
			count += check & 1;

			check >>= 1;
		}

		if (3 == count)
		{
			printf("%d has 3 bits\n", n[i]);
		}
	}
}

int main(void)
{
	unsigned int n[6] = {6,7,3,13,4,19};
	
	HasThreeSetOnBits(n, 6);

	return 0;
}
