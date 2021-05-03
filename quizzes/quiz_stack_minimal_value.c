
int IntStackMinimalValue(stack_t *stack)
{
	int temp = stack->elements[0];
	size_t i = StackSize(stack) - 1;

	for (; i > 0; ++i)
	{
		if (stack->elements[i] < temp)
		{
			temp = stack->elements[i];
		}	
	}

	return temp;
}
