/*****************************************************************************
* title: EndianCheck
* author: aviv illoz
* description: Checks if your computer is Little Endian or Big Endian
******************************************************************************/

#include <stdio.h> 

int CountBits(unsigned char n)
{
	int count = 0;

	while (0 != n)
	{
		++count;

		n &= (n-1);
	}

	return count;
}

int IsLittleEndian(void)
{
	unsigned int i = 1; 

	return (int)&((char *)i);
}

int main(void)  
{
	if (IsLittleEndian())
	{
		printf("little endian!\n");
	}
	else
	{
		printf("big endian!\n");
	}
	
	return 0; 
} 
