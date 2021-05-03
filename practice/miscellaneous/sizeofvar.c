/*****************************************************************************
* title: Size of var
* author: aviv illoz
* description: finds size of var without using sizeof
******************************************************************************/

#include <stdio.h>

#define SIZEOF_VAR(var) (char *)(&var + 1) - (char *)(&var)

int main(void)
{
	double a = 2;

	printf("%ld\n", SIZEOF_VAR(a));

	return 0;
}
