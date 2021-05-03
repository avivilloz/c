/*****************************************************************************
* title: EndianCheck
* author: aviv illoz
* description: Checks if your computer is Little Endian or Big Endian (macro)
******************************************************************************/

#include <stdio.h>
#include <limits.h>
#include <stdint.h>

#if CHAR_BIT != 8
#error "unsupported char size"
#endif

enum
{
	O32_LITTLE_ENDIAN = 0x03020100ul,
	O32_BIG_ENDIAN = 0x00010203ul
};

static const union 
{ 
	unsigned char bytes[4]; 
	uint32_t value; 
} o32_host_order = {{0, 1, 2, 3}};

#define O32_HOST_ORDER (o32_host_order.value)

int main(void)
{
	if (O32_HOST_ORDER == O32_LITTLE_ENDIAN)
	{
		printf("Little Endian\n");
	}
	
	if (O32_HOST_ORDER == O32_BIG_ENDIAN)
	{
		printf("Big Endian\n");
	}
	
	return 0; 
} 
