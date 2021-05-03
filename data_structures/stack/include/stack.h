/****************************************************************************
Title: Stack - Infinity Labs R&D 
Group: Ol91
Description: Stack interface
****************************************************************************/

#ifndef __STACK_H_ILRD_OL91__
#define __STACK_H_ILRD_OL91__

#include <stddef.h> 	/* size_t */

typedef struct stack stack_t;

/****************************************************************************
Decription: 		creating a new stack_t stack; 
Input:			capasity of new stack;
Output:			pointer to new stack;
Error proccessing: 	in case of allocation failure - NULL will be returned;
*/

stack_t *StackCreate(size_t capacity);

/****************************************************************************
Decription: 		freeing memory allocation of a stack; 
Input:			stack_t pointer to a stack;
Output:			-
Error proccessing: 	-
*/
		
void StackDestroy(stack_t *stack);	

/****************************************************************************
Decription: 		adding a new element to the top of a stack; 
Input:			stack_t pointer to a stack, void pointer to a new element;
Output:			-
Error proccessing: 	attempt to push an element to a full stack results in 
			undefined behavior;
*/
	
void StackPush(stack_t *stack, void *element);

/****************************************************************************
Decription: 		poping an element from the top of a stack; 
Input:			stack_t pointer to a stack;
Output:			-
Error proccessing: 	attempt to pop an element from an empty stack results in 
			undefined behavior;
*/

void StackPop(stack_t *stack);

/****************************************************************************
Decription: 		checking an element from the top of a stack; 
Input:			stack_t pointer to a stack;
Output:			pointer to a top element;
Error proccessing: 	attempt to check element from an empty stack results in 
			undefined behavior;
*/

void *StackPeek(const stack_t *stack);	 

/****************************************************************************
Decription: 		getting current number of elements inside stack; 
Input:			stack_t pointer to a stack;
Output:			current number of elements inside stack;
Error proccessing: 	-
*/

size_t StackSize(const stack_t *stack);	 

/****************************************************************************
Decription: 		checking if the stack contains any elements; 
Input:			stack_t pointer to a stack;
Output:			0 - if empty, 1 if not empty;
Error proccessing: 	-
*/

int StackIsEmpty(const stack_t *stack);

/****************************************************************************
Decription: 		checking if the stack contains any elements; 
Input:			stack_t pointer to a stack;
Output:			maximum amount of elements can be stored inside stack;
Error proccessing: 	-
*/

size_t StackCapacity(const stack_t *stack); 

#endif	/*__STACK_H_ILRD_OL91__*/

