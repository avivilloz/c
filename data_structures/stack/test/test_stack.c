/****************************************************************************
Title: Stack - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Nathan
Description: Stack Test API
*****************************************************************************/

#include <stdio.h>	/* printf */
#include "stack.h"	/* api */

int main(void)
{
	size_t a = 32;
	size_t b = 52;
	size_t c = 85;

	/**********************/

	stack_t *stack = StackCreate(5);
	printf("Create Stack!\n");
	printf("\nStack Capacity: %lu\n", StackCapacity(stack));

	/**********************/

	printf("\n/**************************POP**************************/\n");
	printf("\nPush!\n");
	StackPush(stack, &a);
	printf("Peek: %d\n", *(int *)StackPeek(stack));
	printf("Stack Size: %lu\n", StackSize(stack));

	/**********************/

	printf("\nPush!\n");
	StackPush(stack, &b);
	printf("Peek: %d\n", *(int *)StackPeek(stack));
	printf("Stack Size: %lu\n", StackSize(stack));

	/**********************/

	printf("\nPush!\n");
	StackPush(stack, &c);
	printf("Peek: %d\n", *(int *)StackPeek(stack));
	printf("Stack Size: %lu\n", StackSize(stack));

	/**********************/

	printf("\nIs Stack Empty? (1/0): %d\n", StackIsEmpty(stack));

	/**********************/

	printf("\nPop!\n");
	StackPop(stack);
	printf("Peek: %d\n", *(int *)StackPeek(stack));
	printf("Stack Size: %lu\n", StackSize(stack));

	/**********************/

	printf("\nPop!\n");
	StackPop(stack);
	printf("Peek: %d\n", *(int *)StackPeek(stack));
	printf("Stack Size: %lu\n", StackSize(stack));

	/**********************/

	printf("\nPop!\n");
	StackPop(stack);
	printf("Stack Size: %lu\n", StackSize(stack));

	/*********************/

	printf("\nIs Stack Empty? (1/0): %d\n", StackIsEmpty(stack));
	printf("\nStack Capacity: %lu\n", StackCapacity(stack));

	/**********************/

	printf("\n/*************************DESTROY*************************/\n");
	printf("\nPush Again!\n");
	StackPush(stack, &a);
	printf("Peek: %d\n", *(int *)StackPeek(stack));
	printf("Stack Size: %lu\n", StackSize(stack));

	/**********************/

	printf("\nPush Again!\n");
	StackPush(stack, &b);
	printf("Peek: %d\n", *(int *)StackPeek(stack));
	printf("Stack Size: %lu\n", StackSize(stack));

	/**********************/

	printf("\nPush Again!\n");
	StackPush(stack, &c);
	printf("Peek: %d\n", *(int *)StackPeek(stack));
	printf("Stack Size: %lu\n", StackSize(stack));
	
	/**********************/

	printf("\nIs Stack Empty? (1/0): %d\n", StackIsEmpty(stack));

	/**********************/

	printf("\nDestroy!\n");
	StackDestroy(stack);
	printf("\nDestroied.\n");
	
	/**********************/

	printf("\n/**************************END*****************************/\n");	

	return 0;
}

