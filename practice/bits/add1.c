/*****************************************************************************
* title: add one
* author: aviv illoz
* description: adds 1 to an interger using bitwise operations
******************************************************************************/

#include <stdio.h> /* printf */

unsigned int Add1(unsigned int n)
{	
	n = -(~n);
	
	return n;
}

int main(void)
{
	unsigned int n = 16;

	unsigned int result = 0;

	result = Add1(n);

	printf("%u\n", result);

	return 0;
}
