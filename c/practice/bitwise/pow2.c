/*****************************************************************************
* title: pow2
* author: aviv illoz
* description: solves the operation: x*(2^y), using bitwise operations
******************************************************************************/

#include <stdio.h> /* printf */

long Pow2(unsigned int x, unsigned int y)
{
	x <<= y;

	return x;
}

int main(void)
{
	unsigned int x = 4, y = 2;

	long unsigned int result = 0;

	result = Pow2(x, y);

	printf("%lu\n", result);

	return 0;
}
