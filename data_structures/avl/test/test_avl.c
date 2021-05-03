/****************************************************************************
Title: Binary Sorted Tree (Recursive) - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Michail
Description: Binary Sorted Tree (Recursive) Test API
*****************************************************************************/

#include <stdio.h>	/* printf */
#include "avl.h"	/* api */

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

static int IsBefore(const void *lhs, const void *rhs)
{
	return (*(int *)lhs > *(int *)rhs);
}

static int AddInts(void *data, void *params)
{
	*(int *)data += *(int *)params;

	return 0;
}

static test_status_t CreateAndInsert(int array[], avl_t **tree)
{
	size_t i = 0;	
	
	*tree = AVLCreate(IsBefore);
	expect(NULL != *tree);

	expect(1 == AVLIsEmpty(*tree));
	expect(0 == AVLSize(*tree));

	expect(-1 == (int)AVLHeight(*tree));

	for (; i < 10; ++i)
	{
		expect(0 == AVLInsert(*tree, &array[i]));
	}

	expect(0 == AVLIsEmpty(*tree));
	expect(10 == AVLSize(*tree));

	/* after re-balancing (otherwise it would be 4) */
	expect(3 == AVLHeight(*tree));

	return TEST_PASS;
}

static test_status_t ForEachAndFind(avl_t *tree)
{
	size_t i = 0;
	int num = 10;
	int array[10] = {10,11,12,13,14,15,16,17,18,19};	

	AVLForEach(tree, AddInts, &num);

	for (; i < 10; ++i)
	{
		expect(array[i] == *(int *)AVLFind(tree, &array[i]));
	}

	num *= -1;

	AVLForEach(tree, AddInts, &num);

	return TEST_PASS;
}

static test_status_t RemoveCheckSize(avl_t *tree)
{
	int array[] = {5,9,7};

	AVLRemove(tree, &array[0]);
	AVLRemove(tree, &array[1]);
	AVLRemove(tree, &array[2]);

	expect(0 == AVLIsEmpty(tree));
	expect(7 == AVLSize(tree));

	expect(2 == AVLHeight(tree));

	return TEST_PASS;
}

static test_status_t FindAfterRemoved(avl_t *tree)
{
	int array[7] = {0,1,2,3,4,6,8};

	expect(0 == *(int *)AVLFind(tree, &array[0]));
	expect(1 == *(int *)AVLFind(tree, &array[1]));
	expect(2 == *(int *)AVLFind(tree, &array[2]));
	expect(3 == *(int *)AVLFind(tree, &array[3]));
	expect(4 == *(int *)AVLFind(tree, &array[4]));
	expect(6 == *(int *)AVLFind(tree, &array[5]));
	expect(8 == *(int *)AVLFind(tree, &array[6]));

	return TEST_PASS;
}

static test_status_t Test(void)
{
	int success = TRUE;
	avl_t *tree = NULL;
	int array[10] = {3,6,1,4,7,2,8,0,5,9};

	RUN_TEST(CreateAndInsert(array, &tree));
	RUN_TEST(ForEachAndFind(tree));
	RUN_TEST(RemoveCheckSize(tree));
	RUN_TEST(FindAfterRemoved(tree));

	AVLDestroy(tree);

	if (FALSE == success)
	{
		return TEST_FAIL;
	}
	
	return TEST_PASS;
}

/*****************************************************************************/

int main(void)
{
	int success = TRUE;

	RUN_TEST(Test());

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


