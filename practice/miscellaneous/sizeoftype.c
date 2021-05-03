/*****************************************************************************
* title: Size of type
* author: aviv illoz
* description:  finds size of type without using sizeof
******************************************************************************/

#include <stdio.h>

#define SIZEOF_TYPE(type) (char *)(((type *) 0) + 1) - ((char *)0)

int main(void)
{	
	printf("%ld\n", SIZEOF_TYPE(int));

	return 0;
}
