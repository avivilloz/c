/*****************************************************************************
* title: SwapPtrs
* author: aviv illoz
* description: Swaps the addresses of two pointers
******************************************************************************/

#include <stdio.h>	/*for printf*/

void SwapPtrs(int **a, int **b)
{
	int *temp = *a;

	*a = *b;

	*b = temp; 
}

int main(void) 
{
	int n1 = 5, n2 = 7;
	int *ptr1 = &n1, *ptr2 = &n2;

	printf("ptr1 addr is: %p with value %d\n", (void *) ptr1, *ptr1);
	printf("ptr2 addr is: %p with value %d\n", (void *) ptr2, *ptr2);

	SwapPtrs(&ptr1, &ptr2);

	printf("ptr1 addr is: %p with value %d\n", (void *) ptr1, *ptr1);
	printf("ptr2 addr is: %p with value %d\n", (void *) ptr2, *ptr2);

	return 0;
}
