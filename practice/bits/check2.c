/*****************************************************************************
* title: check digits2
* author: Aviv Illoz
* description: Checks if digits 2 and 6 are set on and return true if one is.
******************************************************************************/

#include <stdio.h> /* printf */

unsigned char CheckDigits(unsigned char n) 
{
	return (n & (1 << 1)) || (n & (1 << 5));
}
 
int main(void) 
{ 
	unsigned char n = 1;

	unsigned char result = 0;  

	result = CheckDigits(n);

	printf("%u\n", result); 

	return 0;
} 
