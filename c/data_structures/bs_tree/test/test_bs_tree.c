/****************************************************************************
Title: Binary Sorted Tree
Author: Aviv Illoz
Description: Binary Sorted Tree Test API
*****************************************************************************/

#include <stdio.h>	/* printf */
#include "bs_tree.h"	/* api */

#define expect(x) 	if (!(x))\
			{\
				return TEST_FAIL;\
			}

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
enum {TEST_PASS, TEST_FAIL};

/********************************* TESTS ************************************/

static int IsBefore(const void *lhs, const void *rhs)
{
	return (*(int *)lhs > *(int *)rhs);
}

static int Add(void *data, void *params)
{
	*(int *)data += *(int *)params;

	return 0;
}

static int BSTTest(void)
{
	int num = 10;
	int arr[10] = {4,7,2,5,3,1,9,6,0,8};
	size_t i = 0;
	bst_t *tree = BSTCreate(IsBefore);
	bst_iter_t iter, temp;

	/****************************************/
	printf("Insert and check size");

	expect(0 == BSTSize(tree));
	expect(1 == BSTIsEmpty(tree));

	for (; i < 10; ++i)
	{
		BSTInsert(tree, &arr[i]);
	}

	expect(10 == BSTSize(tree));
	expect(0 == BSTIsEmpty(tree));

	printf(" \33[5;1;32;1mSUCCESS\33[0m\n");

	/****************************************/
	printf("Get Begin Next and Prev");

	iter = BSTBegin(tree);
	expect(0 == *(int *)BSTGetData(iter));

	iter = BSTNext(iter);
	expect(1 == *(int *)BSTGetData(iter));

	iter = BSTPrev(iter);
	expect(0 == *(int *)BSTGetData(iter));

	printf(" \33[5;1;32;1mSUCCESS\33[0m\n");

	/****************************************/	
	printf("Remove, Get Begin Next and Prev");

	iter = BSTNext(iter);
	BSTRemove(iter);
	iter = BSTBegin(tree);
	expect(0 == *(int *)BSTGetData(iter));

	iter = BSTNext(iter);
	expect(2 == *(int *)BSTGetData(iter));

	iter = BSTPrev(iter);
	expect(0 == *(int *)BSTGetData(iter));

	expect(9 == BSTSize(tree));
	expect(0 == BSTIsEmpty(tree));

	printf(" \33[5;1;32;1mSUCCESS\33[0m\n");

	/****************************************/
	printf("Find number 6");

	iter = BSTFind(tree, &arr[7]);
	expect(6 == *(int *)BSTGetData(iter));

	printf(" \33[5;1;32;1mSUCCESS\33[0m\n");

	/****************************************/
	printf("Add Ten to all and print: ");

	BSTForEach(BSTBegin(tree), BSTEnd(tree), Add, &num);

	for (iter = BSTBegin(tree)
		; !BSTIterIsEqual(iter, BSTEnd(tree))
		; iter = BSTNext(iter))
	{
		printf("%d ", *(int *)BSTGetData(iter));
	}

	printf("\33[5;1;32;1mSUCCESS\33[0m\n");

	/****************************************/
	printf("Remove all and check size");

	for (iter = BSTBegin(tree)
		; !BSTIterIsEqual(iter, BSTEnd(tree))
		; iter = temp)
	{
		temp = BSTNext(iter);
		BSTRemove(iter);
	}

	expect(0 == BSTSize(tree));
	expect(1 == BSTIsEmpty(tree));

	printf(" \33[5;1;32;1mSUCCESS\33[0m\n");

	/****************************************/
	printf("Destroy");

	BSTDestroy(tree);

	printf(" \33[5;1;32;1mSUCCESS\33[0m\n");

	return TEST_PASS;
}

/*****************************************************************************/

int main(void)
{
	int success = TRUE;

	RUN_TEST(BSTTest());

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
