/*****************************************************************************
* title: is pow2 loop
* author: aviv illoz
* description: checks of n is a power of 2 using loop and bitwise operations
******************************************************************************/

#include <stdio.h> /* printf */

unsigned int IsPowOf2(unsigned int n)
{	
	unsigned int i = 1;

	for (; i < n; i <<= 1)
	{}
	
	return (i == n);
}

int main(void)
{
	unsigned int n = 15;

	unsigned int result = 0;

	result = IsPowOf2(n);

	printf("%d\n", result);

	return 0;
}
