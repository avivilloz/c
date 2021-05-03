/****************************************************************************
Title: Stack - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Nathan
Description: Stack API
*****************************************************************************/

#include <stdlib.h>	/* malloc */
#include <assert.h>	/* assert */
#include <stddef.h> 	/* size_t */
#include "stack.h"	/* api */

struct stack
{
	size_t capacity;                   
	size_t top_index;                 
	void **elements;                   
};

/*****************************************************************************/

stack_t *StackCreate(size_t capacity)
{
	size_t stack_t_size = sizeof(stack_t);
	size_t stack_size = stack_t_size + (capacity * sizeof(void *));
	stack_t *return_stack = (stack_t *)malloc(stack_size);
	if (NULL == return_stack)
	{
		return NULL;
	}
	
	return_stack->capacity = capacity;
	return_stack->top_index = 0;
	return_stack->elements = (void *)((char *)return_stack + stack_t_size);

	return return_stack;
}

/*****************************************************************************/

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	free(stack);
	stack = NULL;
}

/*****************************************************************************/

void StackPush(stack_t *stack, void *element)
{	
	assert(NULL != stack);
	stack->elements[stack->top_index] = element;
	stack->top_index += 1;
}

/*****************************************************************************/

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	stack->top_index -= 1;
}

/*****************************************************************************/

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack && !StackIsEmpty(stack));
	return stack->elements[stack->top_index - 1];
}

/*****************************************************************************/

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->top_index;
}

/*****************************************************************************/

int StackIsEmpty(const stack_t *stack)
{	
	assert(NULL != stack);
	return (stack->top_index) ? 0 : 1;
}

/*****************************************************************************/

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->capacity;
}

