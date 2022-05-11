#include <stdio.h>
#include <assert.h>
#include "stack.h"

stack_t *StackSort(stack_t *a)
{
	stack_t *b = NULL;
	int *temp_a = 0, *temp_b = 0;

	assert(NULL != a);
	
	b = StackCreate(StackCapacity(a));
	if (NULL == b)
	{
		return NULL;
	}

	temp_b = (int *)StackPeek(a);
	StackPop(a);
	while (!StackIsEmpty(a))
	{
		temp_a = (int *)StackPeek(a);
		StackPop(a);
		if (*temp_a > *temp_b)
		{
			while (!StackIsEmpty(b) && *temp_a > *(int *)StackPeek(b))
			{
				StackPush(a, StackPeek(b));
				StackPop(b);
			}
			StackPush(b, temp_a);
		}
		else 
		{
			StackPush(b, temp_b);
			temp_b = temp_a;
		}
	}
	StackPush(b, temp_b);	

	StackDestroy(a);

	return b;
}

int main(void)
{
	stack_t *a = StackCreate(6);
	int array[6] = {2,5,3,1,4,6};
	size_t i = 0;

	for (; i < StackCapacity(a); ++i)
	{
		StackPush(a, &array[i]);
	}

	a = StackSort(a);

	for (i = 0; !StackIsEmpty(a); ++i)
	{
		printf("%d ", *(int *)StackPeek(a));
		StackPop(a);
	}
	printf("\n");

	StackDestroy(a);

	return 0;
}
