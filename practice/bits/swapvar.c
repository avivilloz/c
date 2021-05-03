/*****************************************************************************
* title: swap variables
* author: aviv illoz
* description: swaps two variables without temp variable
******************************************************************************/

#include <stdio.h> /* printf */

void SwapVar(unsigned int *n1, unsigned int *n2)
{	
	*n1 = *n1 ^ *n2;
	*n2 = *n1 ^ *n2;
	*n1 = *n1 ^ *n2;
}
 
int main(void) 
{ 
	unsigned int n1 = 26;

	unsigned int n2 = 30;

	SwapVar(&n1, &n2);

	printf("%u, %u\n", n1, n2); 

	return 0;
} 
