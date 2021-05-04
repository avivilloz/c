/****************************************************************************
Title: Calculator
Author: Aviv Illoz
Description: Calculator Test API
*****************************************************************************/

#include <stdio.h>		/* printf */
#include "calculator.h"		/* api */

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

/*
 + - / * 
*/
static test_status_t FirstStep(void)
{
	char operation[] = "6*5+66-5";
	double _result = 0;

	expect(SUCCESS == Calculator(operation, &_result));
	expect(91 == _result);

	return TEST_PASS;
}

/*
 ( ) 
*/
static test_status_t SecondStep(void)
{
	char operation[] = "3+5*((9-7)/((2*1)))";
	char operation2[] = /*"(-)"*/"(-)3+5*(-)((9-7)(+)/((2*1)))";
	double _result = 0;

	expect(SUCCESS == Calculator(operation, &_result));
	expect(8 == _result);
	expect(SYNTAX_ERROR == Calculator(operation2, &_result));

	return TEST_PASS;
}

/*
 ^ 
*/
static test_status_t ThirdStep(void)
{
	char operation[] = "(2^2+1)";
	char operation2[] = "(2^2+1)/0";
	double _result = 0;

	expect(SUCCESS == Calculator(operation, &_result));
	expect(5 == _result);
	expect(MATH_ERROR == Calculator(operation2, &_result));

	return TEST_PASS;
}

/*
 unary 
*/
static test_status_t FourthStep(void)
{
	char operation[] = "-3 + --5 * (2 - 7 ^ 2) ^ 3 / -(5-2--(-(-2 * -2)))";
	double _result = 0;
	

	expect(SUCCESS == Calculator(operation, &_result));	
	expect(-519118 == _result);

	return TEST_PASS;
}

/*****************************************************************************/

int main(void)
{
	int success = TRUE;

	RUN_TEST(FirstStep());
	RUN_TEST(SecondStep());
	RUN_TEST(ThirdStep());
	RUN_TEST(FourthStep());
	/*
	*/

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
