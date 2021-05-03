/****************************************************************************
Title: Recursion - Infinity Labs R&D 
Group: OL91
Description: Recursion API
*****************************************************************************/

#ifndef _ILRD_OL91__
#define _ILRD_OL91__

typedef struct node node_t;

#include "stack.h"	/* api */

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

int Fibonacci(int element_index);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

node_t *CreateNode(void *data);

node_t *Insert(node_t *node, void *data);

void *GetData(node_t *node);

node_t *Next(node_t *node);

void Destroy(node_t *head);

node_t *FlipList(node_t *head);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

void StackSort(stack_t *stack, int (*is_bigger)(void *, void *));

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
Time complexity:
*/

size_t Strlen(char *str);

int Strcmp(char *s1, char *s2);

char *Strcpy(char *dest, const char *src);

char *Strcat(char *dest, const char *src);

char *Strstr(const char *haystack, const char *needle);

/*****************************************************************************/

#endif /*_ILRD_OL91__*/

