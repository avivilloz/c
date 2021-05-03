/*****************************************************************************
* title: count bits
* author: aviv illoz
* description: count set on bits in interger without loop.
******************************************************************************/

#include <stdio.h> /* printf */

unsigned int CountSetBits(unsigned int n) 
{ 
	if (0 == n) 
	{
		return 0; 
	}	

	return 1 + CountSetBits(n & (n - 1)); 
}  
 
int main(void) 
{ 
	unsigned int n = 5;

	unsigned int count = CountSetBits(n);

	printf("%d\n", count); 

	return 0;
} 
