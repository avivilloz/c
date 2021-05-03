/*****************************************************************************
* title: check digits
* author: aviv illoz
* description: Checks if digits 2 and 6 are on and return true if both are.
******************************************************************************/

#include <stdio.h> /* printf */

unsigned char CheckDigits(unsigned char n) 
{
	return (n & (1 << 1)) && (n & (1 << 5));
}
 
int main(void) 
{ 
	unsigned char n = 34;

	unsigned char result = 0;  

	result = CheckDigits(n);

	printf("%u\n", result); 

	return 0;
} 
