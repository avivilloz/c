/*****************************************************************************
* title: Macro Max
* author: aviv illoz
* description:  defines max2 and max3
******************************************************************************/

#include <stdio.h>

#define MAX2(a, b) ((a > b) ? a : b)
#define MAX3(a, b, c) ((a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c))

int main(void)
{
	int a = 2, b = 3, c = 4;

	printf("%d, %d\n", MAX2(a, b), MAX3(a, b, c));

	return 0;
}
