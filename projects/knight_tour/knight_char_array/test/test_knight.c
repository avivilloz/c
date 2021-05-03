/*****************************************************************************
Title: Knight Tour - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Sofia
Description: Knight Tour Test API
******************************************************************************/

#include <stdio.h>		/* printf */

#include "knight.h"		/* api */

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

/********************************* TESTS *************************************/

static test_status_t KnightTourTest(void)
{
	int row = 0;
	int column = 0;
	int steps[BOARD_SIZE];

	for (; row < BOARD_LEN; ++row)
	{
		for (column = 0; column < BOARD_LEN; ++column)
		{
			printf("row: %d, column: %d\n", row, column);
			if (SUCCESS == KnightTour(row, column, steps))
			{
				printf("\33[5;1;32;1mSUCCESS\33[0m\n");
			}
			else
			{
				printf("\33[5;1;31mFAILURE\33[0m\n");
			}
			PrintResultPath(steps);
		}
	}

	return TEST_PASS;	
}

/*****************************************************************************/

int main(void)
{
	int success = TRUE;

	RUN_TEST(KnightTourTest());

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


