/*****************************************************************************
* title: byte mirror loop
* author: aviv illoz
* description: reverse bits using loop
******************************************************************************/

#include <stdio.h> /* printf */

unsigned int ByteMirror(unsigned int n)
{
	unsigned int result = 0, check = 0, i = 7;	

	for (; i > 0; i--)
	{
		check = n & 1;
		
		result += (check << i);

		n >>= 1;
	}

	return result;
}
 
int main(void) 
{ 
	unsigned int n = 4;  

	printf("%u\n", ByteMirror(n)); 

	return 0;
} 
