/*****************************************************************************
* title: float analysis
* author: aviv illoz
* description: receives a float and prints its bits for float analysis
******************************************************************************/

#include <stdio.h> /* printf */

typedef unsigned int uint;

int GetBit(uint n, size_t index)
{
	return ((n >> index) & 1U);
}

void PrintBits(uint n) 
{ 
	int i = (sizeof(n) * 8) - 1;

    	for (; i >= 0; --i)
    	{
        	printf("%d", GetBit(n, i));
    	}
	
	printf("\n");
}
 
int main(void) 
{ 
	float n = 18.5;

	PrintBits(*(uint *)&n);

	return 0;
} 
