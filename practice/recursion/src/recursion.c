/****************************************************************************
Title: Recursion - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: Recursion API
*****************************************************************************/

#include <stdlib.h>	/* malloc */
#include "recursion.h"	/* api */

/*****************************************************************************/

int Fibonacci(int element_index)
{
	static int next = 1;
	static int result = 0;
	int temp = 0;

	if (0 == element_index)
	{
		return result;
	}
	
	--element_index;

	temp = next;
	next += result;
	result = temp;

	return Fibonacci(element_index);
}

/*****************************************************************************/

struct node
{
	void *data;
	node_t *next;
};

node_t *CreateNode(void *data)
{
	node_t *node = malloc(sizeof(node_t));
	if (NULL == node)
	{
		return NULL;
	}

	node->data = data;
	node->next = NULL;

	return node;
}

node_t *Insert(node_t *node, void *data)
{
	node_t *tail = malloc(sizeof(node_t));
	if (NULL == tail)
	{
		return NULL;
	}

	node->next = tail;

	tail->data = data;
	tail->next = NULL;

	return tail;
}

void *GetData(node_t *node)
{
	return node->data;
}

node_t *Next(node_t *node)
{
	return node->next;
}	

void Destroy(node_t *head)
{
	node_t *temp = head;
	for (head = Next(head); NULL != temp->next; temp = head, head = Next(head))
	{
		free(temp);
		temp = NULL;
	}
	free(temp);
	temp = NULL;
}

node_t *FlipList(node_t *head)
{
	static node_t *prev = NULL;
	node_t *curr = head;
	node_t *temp = curr->next;

	if (NULL == curr->next)
	{
		curr->next = prev;
		return curr;
	}
	
	curr->next = prev;
	prev = curr;

	return FlipList(temp);
}

/*****************************************************************************/

static void StackSortedInsert(
	stack_t *stack, 
	void *element, 
	int (*is_bigger)(void *, void *)
)
{
	void *temp = NULL;

	if (StackIsEmpty(stack) || is_bigger(element, StackPeek(stack)))
	{
		StackPush(stack, element);	
	}
	else
	{
		temp = StackPeek(stack);
		StackPop(stack);
		StackSortedInsert(stack, element, is_bigger);
		StackPush(stack, temp);		
	}
}

void StackSort(stack_t *stack, int (*is_bigger)(void *, void *))
{
	void *temp = NULL;

	if (!StackIsEmpty(stack))
	{
		temp = StackPeek(stack);
		StackPop(stack);
		StackSort(stack, is_bigger);
		StackSortedInsert(stack, temp, is_bigger);
	}
}

/*****************************************************************************/

static int IsEndOfStr(char element)
{
	return ('\0' == element);
}

size_t Strlen(char *str)
{
	if (IsEndOfStr(*str))
	{
		return 0;
	}

	return 1 + Strlen(str + 1);
}

/*****************************************************************************/

int Strcmp(char *s1, char *s2)
{
	if (0 != *s1 - *s2 || IsEndOfStr(*s1) || IsEndOfStr(*s2))
	{
		return *s1 - *s2;
	}

	return Strcmp(s1 + 1, s2 + 1);
}

/*****************************************************************************/

char *Strcpy(char *dest, const char *src)
{
	*dest = *src;

	if (IsEndOfStr(*src))
	{
		return dest;
	}

	return Strcpy(dest + 1, src + 1) - 1;
}

/*****************************************************************************/

char *Strcat(char *dest, const char *src)
{
	if (!IsEndOfStr(*dest))
	{
		Strcat(dest + 1, src);
	}
	else if (!IsEndOfStr(*src))
	{
		*dest = *src;
		*(dest + 1)  = '\0';
		return Strcat(dest + 1, src + 1);
	}

	return dest;
}

/*****************************************************************************/

char *Strstr(const char *haystack, const char *needle)
{
	if (IsEndOfStr(*needle))
	{
		return (char *)haystack;
	}
	
	if (*haystack == *needle)
	{
		return Strstr(haystack + 1, needle + 1) - 1;
	}

	if (!IsEndOfStr(*haystack))
	{
		return Strstr(haystack + 1, needle);
	}

	return NULL;
}

