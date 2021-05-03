/*****************************************************************************
* title: count bits
* author: aviv illoz
* description: count set on bits in interger.
******************************************************************************/

#include <stdio.h> /* printf */

unsigned int CountSetBits(unsigned int n)  
{  
	unsigned int count = 0, i = 0;

	for (; i < 32; i++)
	{
		count += n & 1;
	
		n >>= 1;
	}

	return count;
}  
 
int main(void) 
{ 
	unsigned int n = 5;

	unsigned int count = CountSetBits(n);

	printf("%u\n", count); 

	return 0;
} 
