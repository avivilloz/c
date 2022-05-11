/*****************************************************************************
* title: byte mirror
* author: aviv illoz
* description: reverse bits with no loops
******************************************************************************/

#include <stdio.h>	/* printf */

unsigned char ByteMirror(unsigned char n) 
{
	n = (n & 0xF0) >> 4 | (n & 0x0F) << 4;
	n = (n & 0xCC) >> 2 | (n & 0x33) << 2;
	n = (n & 0xAA) >> 1 | (n & 0x55) << 1;

	return n;
}
 
int main(void) 
{ 
	unsigned char n = 5;  

	printf("%u\n", ByteMirror(n)); 

	return 0;
} 
