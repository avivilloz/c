/*****************************************************************************
* title: divisible by 16
* author: aviv illoz
* description: it checks the closest number to num disvisible by 16
******************************************************************************/

#include <stdio.h> /* printf */

unsigned int DivBy16(unsigned int n)
{		
	n >>= 4;
	n <<= 4; 
	
	return n;
}
 
int main(void) 
{ 
	unsigned int n = 16;  

	printf("%u\n", DivBy16(n)); 

	return 0;
} 
