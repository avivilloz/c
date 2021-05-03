/*****************************************************************************
Title: knowladge_sampling_exam 
Description: learn knowladge_sampling_exam
******************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

/*****************************************************************************/

/* count bits */

size_t CountBits(unsigned char n)
{
	size_t count = 0;

	while (0 != n)
	{
		++count;
		n &= (n - 1);
	}

	return count;
}

size_t CountBitsO1(unsigned char n)
{
	n = (n & 0x55) + ((n >> 1) & 0x55);
	n = (n & 0x33) + ((n >> 2) & 0x33);
	n = (n & 0x0F) + ((n >> 4) & 0x0F);

	return n;
}

/* mirror bits */

static const size_t g_char_bits = sizeof(char) * CHAR_BIT; 

unsigned char MirrorBits(unsigned char n)
{
	unsigned char result = 0;
	size_t i = 0, half = g_char_bits / 2, offset = g_char_bits - 1;

	for (; i < half; ++i)
	{
		result |= ((1 & (n >> i)) << (offset - i));
		result |= ((1 & (n >> (offset - i))) << i);
	}
	
	return result;
}

unsigned char MirrorBitsO1(unsigned char n)
{
	n = ((n & 0xAA) >> 1) | ((n & 0x55) << 1);
	n = ((n & 0xCC) >> 2) | ((n & 0x33) << 2);
	n = ((n & 0xF0) >> 4) | ((n & 0x0F) << 4);

	return n;
}

uint32_t MirrorBitsUint32(uint32_t n)
{
	n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
	n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
	n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
	n = ((n & 0xFF00FF00) >> 4) | ((n & 0x00FF00FF) << 8);
	n = ((n & 0xFFFF0000) >> 4) | ((n & 0x0000FFFF) << 16);

	return n;
}

/* is pow 2 */

int IsPow2(unsigned int n)
{
	return (0 == (n & (n - 1)));
}

/* shift rotate right */

static const size_t g_int_bits = sizeof(int) * CHAR_BIT;

unsigned int ShiftRotateRight(unsigned int n, size_t i)
{
	return (n << (g_int_bits - i)) | (n >> i);
}


/* flip singly linked list */

typedef struct node node_t;

struct node
{
	int data;
	node_t *next;
};

node_t *CreateList(int arr[], size_t size)
{
	size_t i = 0;

	node_t *head = malloc(sizeof(node_t));
	/* check */
	node_t *curr = head;
	curr->data = arr[i];

	for (++i; i < size; ++i)
	{
		curr->next = malloc(sizeof(node_t));
		/* check */
		curr->next->data = arr[i];
		curr = curr->next;
	}
	curr->next = NULL;

	return head;
}

void PrintList(node_t *head)
{
	node_t *curr = head;

	for (; NULL != curr; curr = curr->next)
	{
		printf("%d ", curr->data);
	}
	puts("");
}

node_t *FlipList(node_t *head)
{
	node_t *prev = NULL;
	node_t *curr = head;

	while (NULL != curr)
	{
		node_t *next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	return prev;
}

node_t *FlipListRec(node_t *curr)
{
	node_t *prev = NULL, *head = NULL;

	if (NULL == curr->next)
	{
		return curr;
	}

	head = FlipListRec(curr->next);
	curr->next->next = curr;
	curr->next = prev;

	return head;
}

/* print tree recursevely */

enum {RIGHT, LEFT, NUM_OF_CHILDREN};

typedef struct bst_node bst_node_t;

struct bst_node
{
	int data;
	bst_node_t *children[NUM_OF_CHILDREN];
};

static void InsertInBst(bst_node_t *root, bst_node_t *node)
{
	bst_node_t *curr = root;
	int side = (node->data < curr->data);

	while (NULL != curr->children[side])
	{
		curr = curr->children[side];
		side = (node->data < curr->data);
	}

	curr->children[side] = node;
}

bst_node_t *CreateBst(int arr[], size_t size)
{
	size_t i = 0;

	bst_node_t *root = malloc(sizeof(bst_node_t));
	/* check */
	root->data = arr[i];
	root->children[LEFT] = NULL;
	root->children[RIGHT] = NULL;

	for (++i; i < size; ++i)
	{
		bst_node_t *next = malloc(sizeof(bst_node_t));
		/* check */
		next->data = arr[i];
		next->children[LEFT] = NULL;
		next->children[RIGHT] = NULL;
		InsertInBst(root, next);
	}

	return root;
}

void PrintBstRecInOrder(bst_node_t *node)
{
	if (NULL == node)
	{
		return;
	}

	PrintBstRecInOrder(node->children[LEFT]);
	printf("%d ", node->data);
	PrintBstRecInOrder(node->children[RIGHT]);
}

void PrintBstRecPreOrder(bst_node_t *node)
{
	if (NULL == node)
	{
		return;
	}

	printf("%d ", node->data);
	PrintBstRecPreOrder(node->children[LEFT]);
	PrintBstRecPreOrder(node->children[RIGHT]);
}

void PrintBstRecPostOrder(bst_node_t *node)
{
	if (NULL == node)
	{
		return;
	}

	PrintBstRecPostOrder(node->children[LEFT]);
	PrintBstRecPostOrder(node->children[RIGHT]);
	printf("%d ", node->data);
}

/* print tree iteratively */

typedef struct stack_bst stack_bst_t;

struct stack_bst
{
	bst_node_t **stack;
	int capacity;
	int top;
};

stack_bst_t *CreateBstStack(size_t capacity)
{
	stack_bst_t * new_stack = malloc(sizeof(stack_bst_t));
	/* check */
	new_stack->stack = malloc(sizeof(bst_node_t) * capacity);
	new_stack->capacity = capacity;
	new_stack->top = 0;

	return new_stack;
}

size_t BstSize(bst_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}

	return 1 + BstSize(node->children[LEFT]) + BstSize(node->children[RIGHT]);
}

void StackBstPush(stack_bst_t *s, bst_node_t *node)
{
	if (s->capacity == s->top)
	{
		return;
	}

	s->stack[s->top] = node;
	++s->top;
}

bst_node_t *StackBstPop(stack_bst_t *s)
{
	if (0 == s->top)
	{
		return NULL;
	}

	--s->top;
	return s->stack[s->top];
}

void PrintBstPreOrder(bst_node_t *root)
{
	stack_bst_t *s = CreateBstStack(BstSize(root));
	/* check */

	while (NULL != root)
	{
		printf("%d ", root->data);
		if (NULL != root->children[RIGHT])
		{
			StackBstPush(s, root->children[RIGHT]);
		}
		if (NULL != root->children[LEFT])
		{
			StackBstPush(s, root->children[LEFT]);
		}
		root = StackBstPop(s);
	}
}

/* fibonacci */

unsigned int Fibonacci(int i)
{
	unsigned int prev = 0, curr = 1;

	for (; i > 0 ; --i)
	{
		unsigned int next = prev + curr;
		prev = curr;
		curr = next;
	}

	return prev;
}

unsigned int FibonacciRec(int i, unsigned int prev, unsigned int curr)
{
	if (0 == i)
	{
		return prev;
	}

	return FibonacciRec(i - 1, curr, prev + curr);
}

unsigned int CallFibonacciRec(size_t i)
{
	return FibonacciRec(i, 0, 1);
}

/* sort stack */

typedef struct stack stack_t;

struct stack
{
	int *stack;
	int capacity;
	int top;
};

stack_t *CreateStack(size_t capacity)
{
	stack_t * new_stack = malloc(sizeof(stack_t));
	/* check */
	new_stack->stack = malloc(sizeof(int) * capacity);
	new_stack->capacity = capacity;
	new_stack->top = 0;

	return new_stack;
}

void StackPush(stack_t *s, int data)
{
	if (s->capacity == s->top)
	{
		exit(1);
	}

	s->stack[s->top] = data;
	++s->top;
}

int StackPop(stack_t *s)
{
	if (0 == s->top)
	{
		exit(1);
	}

	--s->top;
	return s->stack[s->top];
}

void CopyArrToStack(stack_t *s, int arr[], size_t size)
{
	size_t i = 0;

	for (; i < size; ++i)
	{
		StackPush(s, arr[i]);
	}
}

size_t StackSize(stack_t *s)
{
	return s->top;
}

int StackIsEmpty(stack_t *s)
{
	return (0 == s->top);
}

void PrintStack(stack_t *s)
{
	int i = s->top - 1;

	for (; i >= 0; --i)
	{
		printf("%d ", s->stack[i]);
	}
	printf("\n");
}

void StackSort(stack_t *s1)
{
	size_t i = StackSize(s1), j = 0;
	stack_t *s2 = CreateStack(StackSize(s1));
	/* check */
	
	for (; i > 0; --i)
	{
		int max = StackPop(s1);
		for (j = 1; j < i; ++j)
		{
			int curr = StackPop(s1);

			if (max < curr)
			{
				int temp = max;
				max = curr;
				curr = temp;
			}

			StackPush(s2, curr);
		}

		StackPush(s1, max);

		while (!StackIsEmpty(s2))
		{
			StackPush(s1, StackPop(s2));
		}

	}
}

void StackSortRec(stack_t *s, int max, size_t i)
{
	int to_push = 0;

	if (1 == i)
	{
		StackPush(s, max);
		return;
	}

	to_push = StackPop(s);

	if (max < to_push)
	{
		int temp = max;
		max = to_push;
		to_push = temp;
	}

	StackSortRec(s, max, i - 1);
	StackPush(s, to_push);
}

void CallStackSortRec(stack_t *s)
{
	size_t i = 0;

	if (StackIsEmpty(s))
	{
		return;
	}
	
	for (i = StackSize(s); i > 0; --i)
	{
		StackSortRec(s, StackPop(s), i);
	}
}

/* memcpy */

void PrintIntArr(int arr[], size_t size)
{
	size_t i = 0;
	
	for (; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
	puts("");
}

void PrintCharArr(char arr[], size_t size)
{
	size_t i = 0;
	
	for (; i < size; ++i)
	{
		printf("%c ", arr[i]);
	}
	puts("");
}

void *Memcpy(void *dest, const void *src, size_t nbytes)
{
	char *curr_dest = (char *)dest;
	char *curr_src = (char *)src;

	for (; nbytes > 0; --nbytes)
	{
		*curr_dest = *curr_src;
		++curr_dest;
		++curr_src;
	}

	return dest;
}

void *Memset(void *dest, char c, size_t nbytes)
{
	char *curr_dest = (char *)dest;

	for (; nbytes > 0; --nbytes)
	{
		*curr_dest = c;
		++curr_dest;
	}
	
	return dest;
}

/* open loop */

void CreateLoop(node_t* head, size_t victim)
{
	size_t i = 0;
	node_t *victim_node = NULL;
	node_t *curr = head;

	while (NULL != curr->next)
	{
		if (victim == i)
		{
			victim_node = curr;
		}

		curr = curr->next;
		++i;
	}

	curr->next = victim_node;
}

nt HasLoop(node_t *head)
{
	node_t *slow = head;
	node_t *fast = slow->next;

	while (NULL != fast->next)
	{
		if (fast == slow)
		{
			return 1;
		}

		slow = slow->next;
		fast = fast->next->next;
	}

	return 0;
}

void OpenLoop(node_t *head)
{
	int opened = 0;
	node_t *opener = head;
	node_t *slow = head;
	node_t *fast = slow->next;

	while (!opened)
	{
		if (opener == fast->next)
		{
			fast->next = NULL;
			opened = 1;
		}
		else if (opener == fast->next->next)
		{
			fast->next->next = NULL;
			opened = 1;
		}
		else if (fast == slow)
		{
			opener = opener->next;
			slow = opener;
			fast = slow->next;
		}
		else
		{
			slow = slow->next;
			fast = fast->next->next;
		}
	}
}

void OpenLoopON(node_t *head)
{
	node_t *slow = head;
	node_t *fast = slow->next;

	while (fast != slow)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	slow = head;

	while (fast->next != slow)
	{
		slow = slow->next;
		fast = fast->next;
	}

	fast->next = NULL;
}

int main(void)
{
	/* count bits */
	/*
	printf("%ld\n", CountBits(15));	
	printf("%ld\n", CountBitsO1(15));	
	*/
	/* mirror bits */
	/*
	printf("%c\n", MirrorBits(140));
	printf("%c\n", MirrorBitsO1(140));
	printf("%d\n", MirrorBitsUint32(140));
	*/
	/* is pow 2 */
	/*
	printf("%d\n", IsPow2(16));
	printf("%d\n", IsPow2(32));
	printf("%d\n", IsPow2(34));
	*/
	/* shift rotate right */
	/*
	printf("%d\n", ShiftRotateRight(17, 2));
	*/
	/* flip list */
	/*
	{
		int arr[5] = {1,2,3,4,5};
		node_t *head1, *head2;

		head1 = CreateList(arr, 5);
		PrintList(head1);
		head1 = FlipList(head1);
		PrintList(head1);

		head2 = CreateList(arr, 5);
		PrintList(head2);
		head2 = FlipListRec(head2);
		PrintList(head2);
	}
	*/
	/* print tree recursevely */
	/*
	{
		int arr[5] = {1,2,3,4,5};
		bst_node_t *root = CreateBst(arr, 5);
		PrintBstRecInOrder(root);
		puts("");
		PrintBstRecPreOrder(root);
		puts("");
		PrintBstRecPostOrder(root);
		puts("");
	}
	*/
	/* print tree iteratively */
	/*
	{
		int arr[5] = {1,2,3,4,5};
		bst_node_t *root = CreateBst(arr, 5);
		PrintBstPreOrder(root);
		puts("");
	}
	*/
	/* fibonacci */
	/*
	printf("%u\n", Fibonacci(5));
	printf("%u\n", CallFibonacciRec(5));
	*/
	/* stack sort */
	/*
	{
		int arr[5] = {4,2,7,3,0};
		stack_t *s = CreateStack(5);
		CopyArrToStack(s, arr, 5);
		PrintStack(s);
		StackSort(s);
		PrintStack(s);
	}	
	*/
	/* stack sort rec */
	/*
	{
		int arr[5] = {4,2,7,3,0};
		stack_t *s = CreateStack(5);
		CopyArrToStack(s, arr, 5);
		PrintStack(s);
		CallStackSortRec(s);
		PrintStack(s);
	}	
	*/
	/* memcpy */
	/*
	{
		int src[5] = {1,2,3,4,5};
		int dest[5];
		Memcpy(dest, src, 5 * sizeof(int));
		PrintIntArr(dest, 5);
	}
	*/
	/* memset */
	/*
	{
		char dest[5];
		Memset(dest, 'A', 5);
		PrintCharArr(dest, 5);
	}
	*/
	/* open loop O(n square) */
	/*
	{ 
		int arr[5] = {1,2,3,4,5};
		node_t *head = CreateList(arr, 5);
		CreateLoop(head, 2);
		printf("has loop? %d\n", HasLoop(head));
		OpenLoop(head);
		puts("loop opened");
		PrintList(head);
	}
	*/
	/* open loop O(n) */
	/*
	{
		int arr[5] = {1,2,3,4,5};
		node_t *head = CreateList(arr, 5);
		CreateLoop(head, 1);
		printf("has loop? %d\n", HasLoop(head));
		OpenLoopON(head);
		puts("loop opened");
		PrintList(head);
	}
	*/

	return 0;
}

/*****************************************************************************/

