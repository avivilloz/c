/****************************************************************************
Title: Recursion - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: Recursion Test API
*****************************************************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc */
#include "recursion.h"	/* api */

#define expect(x)	if (!(x))\
			{\
				return TEST_FAIL;\
			}\

#define RUN_TEST(x)	if (TEST_FAIL == (x))\
			{\
				printf("%s: \33[5;1;31mFAILURE\33[0m\n", #x);\
				success = FALSE;\
			}\
			else\
			{\
				printf("%s: \33[5;1;32;1mSUCCESS\33[0m\n", #x);\
			}

/*****************************************************************************/

enum {FALSE, TRUE};
typedef enum {TEST_PASS, TEST_FAIL} test_status_t;

/********************************* TESTS ************************************/

static test_status_t TestFibonacci(void)
{
	expect(8 == Fibonacci(6));

	return TEST_PASS;
}

static test_status_t TestFlipList(void)
{
	int array[5] = {1,2,3,4,5};
	int i = 0;
	node_t *head = CreateNode(&array[i]);
	node_t *node = head;

	for (i = 1; i < 5; ++i)
	{
		node = Insert(node, &array[i]);
	}

	for (i = 0, node = head; i < 5; ++i, node = Next(node))
	{
		printf("%d ", *(int *)GetData(node));
	}
	printf("\n");

	head = FlipList(head);
	
	for (i = 4, node = head; i >= 0; --i, node = Next(node))
	{
		expect(array[i] == *(int *)GetData(node));
		printf("%d ", *(int *)GetData(node));
	}
	printf("\n");

	Destroy(head);

	return TEST_PASS;
}

static int IntIsBigger(void *lhs, void *rhs)
{
	return (*(int *)lhs > *(int *)rhs);
}

static test_status_t TestStackSort(void)
{
	int array[5] = {4,2,5,3,1};
	int i = 0;
	stack_t *stack = StackCreate(5);
	
	for (; i < 5; ++i)
	{
		StackPush(stack, &array[i]);
	}

	for (; !StackIsEmpty(stack); StackPop(stack))
	{
		printf("%d ", *(int *)StackPeek(stack));
	}
	printf("\n");	

	for (i = 0; i < 5; ++i)
	{
		StackPush(stack, &array[i]);
	}

	StackSort(stack, IntIsBigger);

	for (i = 5; !StackIsEmpty(stack); --i, StackPop(stack))
	{
		expect(i == *(int *)StackPeek(stack));
		printf("%d ", *(int *)StackPeek(stack));
	}
	printf("\n");

	StackDestroy(stack);

	return TEST_PASS;
}

static test_status_t TestStrlen(void)
{
	char *str = "Hi my name is Aviv";

	expect(18 == Strlen(str));

	return TEST_PASS;
}

static test_status_t TestStrcmp(void)
{
	char *s1 = "Hi my name is Aviv";
	char *s2 = "Hi my name is ";

	expect(65 == Strcmp(s1, s2));

	return TEST_PASS;
}

static test_status_t TestStrcpy(void)
{
	char *src = "Hi my name is Aviv";
	char *dest = (char *)malloc(19);
	size_t i = 0; 

	dest = Strcpy(dest, src);

	for (; '\0' != *src; ++src, ++i)
	{
		expect(dest[i] == *src);
	}

	free(dest);
	dest = NULL;

	return TEST_PASS;
}

static test_status_t TestStrcat(void)
{
	char *s1 = (char *)malloc(100); 
	char *temp = "Hi my name is Aviv";
	char *s2 = " I'm 24 years old";
	char *s3 = "Hi my name is Aviv I'm 24 years old";
	size_t i = 0;

	s1 = Strcpy(s1, temp);
	s1 = Strcat(s1, s2);

	printf("%s\n%s\n", s3, s1);

	for (; '\0' != *s3; ++s3, ++i)
	{
		expect(s1[i] == *s3);
	}

	free(s1);
	s1 = NULL;

	return TEST_PASS;
}

static test_status_t TestStrstr(void)
{
	char *s1 = "Hi my name is Aviv I'm 24 years old";
	char *s2 = " I'm 24 years old";
	
	expect(&s1[18] == Strstr(s1, s2));

	return TEST_PASS;
}

/*****************************************************************************/

int main(void)
{
	int success = TRUE;

	RUN_TEST(TestFibonacci());
	RUN_TEST(TestFlipList());
	RUN_TEST(TestStackSort());
	RUN_TEST(TestStrlen());
	RUN_TEST(TestStrcmp());
	RUN_TEST(TestStrcpy());
	RUN_TEST(TestStrcat());
	RUN_TEST(TestStrstr());

	if (success)
	{
		printf("Test was a: \33[5;1;32;1mSUCCESS\33[0m\n");
	}
	else
	{
		printf("Test was a: \33[5;1;31mFAILURE\33[0m\n");
	}

	return 0;
}


