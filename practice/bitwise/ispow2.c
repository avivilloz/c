/*****************************************************************************
* title: is pow2
* author: aviv illoz
* description: checks of n is a power of 2 using bitwise operations
******************************************************************************/

#include <stdio.h> /* printf */

unsigned int IsPowOf2(unsigned int n)
{
	unsigned int result = 0;
	
	if ((n & (n - 1)) == 0)
	{
		result = 1;
	}

	/* or just do return !!(n & (n-1));*/
	
	return result;
}

int main(void)
{
	unsigned int n = 16;

	unsigned int result = 0;

	result = IsPowOf2(n);

	printf("%u\n", result);

	return 0;
}
