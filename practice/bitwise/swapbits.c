/*****************************************************************************
* title: swap bits
* author: aviv illoz
* description: swap digits 3 and 5
******************************************************************************/

#include <stdio.h> /* printf */

unsigned char SwapDigits(unsigned char n) 
{
	int result = 0, check = 0, i = 0;

	check = (n >> 2) & 1;

	check <<= 4;

	result = result | check;

	check = (n >> 4) & 1;

	check <<= 2;

	result = result | check;

	for (check = 0; i < 8; i++)
	{
		if (2 == i || 4 == i)
		{
			i++;
		}

		check = (n >> i) & 1;

		check <<= i;

		result = result | check;
	}

	return result;
}
 
int main(void) 
{ 
	unsigned char n = 12;

	unsigned char result = 0;  

	result = SwapDigits(n);

	printf("%u\n", result); 

	return 0;
} 
