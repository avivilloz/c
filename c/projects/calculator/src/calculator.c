/****************************************************************************
Title: Calculator
Author: Aviv Illoz
Description: Calculator Interface
*****************************************************************************/

#include <stdlib.h>	/* malloc */
#include <assert.h>	/* assert */
#include <string.h>	/* strlen */

#include "calculator.h"	/* api */
#include "stack.h"	/* api */

#define BYTE_SIZE 256

/*****************************************************************************/

typedef enum {FIRST, SECOND, THIRD, FOURTH} priority_check_t;
typedef enum {OPERAND, OPERATOR, INVALID} elem_check_t;
typedef enum {OFF, ON} unary_status_t;

typedef struct operand
{
	double num;
} operand_t;

typedef struct operator
{
	char operator;
	unary_status_t unary_status;
} operator_t;

typedef struct operation
{
	unsigned int priority;
	double (*operation)(double, double);
} operation_t;

static int CHECK_PARENTHESES = 0;
static char LAST_ELEMENT = '\0';

/*********************** MAIN FUNCTIONS DECLARATIONS *************************/

calc_status_t Calculator(const char *input, double *_result);
static void *CreateDummy(void);
static void InitOperatorsLut(operation_t lut[]);
static void DestroyElements(stack_t *operators, stack_t *operands);

/**************************************/

static calc_status_t RunCalculator(
	const char *input,
	double *_result,
	stack_t *operands,
	stack_t *operators,
	operation_t lut[]
);
static void JumpSpaces(char **runner);
static elem_check_t CheckInput(char element);
static calc_status_t FinishOperation(
	stack_t *operands, 
	stack_t *operators, 	
	double *_result, 
	operation_t lut[]
);

/**************************************/

static calc_status_t AnalizeOperand(
	char **runner, 
	stack_t *operands,
	stack_t *operators,
	operation_t lut[]
);
static double LexAndParseOperand(char **runner);
static void JumpDot(char **runner);
static void CheckForUnary(
	stack_t *operators, 
	stack_t *operands, 
	operation_t lut[]
);

/**************************************/

static calc_status_t AnalizeOperator(
		char **runner, 
		stack_t *operands, 
		stack_t *operators, 
		operation_t lut[]
);
static calc_status_t PushToStack(stack_t *operators, char element);

/**************************************/

static calc_status_t PerformOperation(
	stack_t *operands, 
	stack_t *operators, 
	operation_t lut[]
);

/********************************* OPERATIONS ********************************/

static double Add(double first_operand, double top_operand)
{
	return first_operand + top_operand;
}

static double Subtract(double first_operand, double top_operand)
{
	return first_operand - top_operand;
}

static double Multiply(double first_operand, double top_operand)
{
	return first_operand * top_operand;
}

static double Divide(double first_operand, double top_operand)
{
	return first_operand / top_operand;
}

static double RaiseByPower(double temp, double power)
{
	double result = 1;

	if (power < 0)
	{
		temp = 1/temp;
		power *= -1;
	}

	for (; power > 0; --power)
	{
		result *= temp;
	}

	return result;
}

/**************************** 'IS' FUNCTIONS *********************************/

static int IsOperand(char element)
{
	return (48 <= element && 57 >= element);
}

static int IsOperator(char element)
{
	return ((40 <= element && 47 >= element 
		&& 44 != element && 46 != element)
		|| 94 == element);
}

static int IsDot(char element)
{
	return ('.' == element);
}

static int IsOpenParentheses(char element)
{
	return ('(' == element);
}

static int IsCloseParentheses(char element)
{
	return (')' == element);
}

static int IsParentheses(char element)
{
	if (IsOpenParentheses(element))
	{
		return 1;
	}
	else if (IsCloseParentheses(element))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

static int ParenthesesNotClosed(void)
{
	return (CHECK_PARENTHESES > 0);
}

static int ParenthesesNotOpened(void)
{
	return (CHECK_PARENTHESES < 0);
}

static int IsDivision(char element)
{
	return ('/' == element);
}

static int IsPower(char element)
{
	return ('^' == element);
}

static int IsEndOfInput(char element)
{
	return ('\0' == element);
}

static int IsUnary(char element)
{
	return ('-' == element || '+' == element);
}

static int IsUnaryOperator(char element)
{
	return (IsUnary(element) 
		&& IsOperator(LAST_ELEMENT) 
		&& !IsCloseParentheses(LAST_ELEMENT));
}

static int IsHigherPriority(
	char operator,
	char top_operator,
	operation_t lut[]
)
{	
	if (IsPower(operator) && IsPower(top_operator))
	{
		return 1;
	}
	
	return (lut[operator].priority < lut[top_operator].priority);
}

static int IsMathError(
	stack_t *operands, 
	stack_t *operators
)
{
	operator_t *operator = (operator_t *)StackPeek(operators);
	operand_t *top_operand = (operand_t *)StackPeek(operands);

	if (IsDivision(operator->operator) && 0 == top_operand->num)
	{
		return 1;
	}

	return 0;
}

/**************************** MAIN FUNCTIONS *********************************/

calc_status_t Calculator(const char *input, double *_result)
{
	stack_t *operands = NULL;
	stack_t *operators = NULL;
	void *dummy = NULL;
	operation_t operators_lut[BYTE_SIZE];
	calc_status_t check = SUCCESS;

	assert(NULL != input && NULL != _result);

	operands = StackCreate(strlen(input));
	if (NULL == operands)
	{
		return SYS_ERROR;
	}

	operators = StackCreate(strlen(input));
	if (NULL == operators)
	{
		StackDestroy(operands);
		return SYS_ERROR;
	}

	dummy = CreateDummy();

	StackPush(operators, dummy);

	InitOperatorsLut(operators_lut);

	check = RunCalculator(
			input,
			_result,
			operands,
			operators,
			operators_lut);

	if (SUCCESS != check)
	{
		DestroyElements(operators, operands);
	}

	StackDestroy(operands);
	operands = NULL;

	StackDestroy(operators);
	operators = NULL;

	return check;
}

static void *CreateDummy(void)
{
	operator_t *dummy = (operator_t *)malloc(sizeof(operator_t));
	if (NULL == dummy)
	{
		return NULL;
	}

	dummy->operator = '(';
	dummy->unary_status = OFF;

	return (void *)dummy;
}

static void InitOperatorsLut(operation_t lut[])
{
	lut['+'].priority = FOURTH;
	lut['+'].operation = Add;

	lut['-'].priority = FOURTH;
	lut['-'].operation = Subtract;

	lut['*'].priority = THIRD;
	lut['*'].operation = Multiply;

	lut['/'].priority = THIRD;
	lut['/'].operation = Divide;

	lut['^'].priority = SECOND;
	lut['^'].operation = RaiseByPower;

	lut['('].priority = FIRST;
	lut['('].operation = NULL;

	lut[')'].priority = FOURTH;
	lut[')'].operation = NULL;
}

static void DestroyElements(stack_t *operators, stack_t *operands)
{
	while (!StackIsEmpty(operators))
	{
		free(StackPeek(operators));
		StackPop(operators);
	}

	while (!StackIsEmpty(operands))
	{
		free(StackPeek(operands));
		StackPop(operands);
	}

	CHECK_PARENTHESES = 0;
}

/*****************************************************************************/

static calc_status_t RunCalculator(
	const char *input,
	double *_result,
	stack_t *operands,
	stack_t *operators,
	operation_t lut[]
)
{
	char *runner = (char *)input;
	char temp = '\0';
	calc_status_t check = SUCCESS;
	
	for (LAST_ELEMENT = *runner
		; !IsEndOfInput(*runner) && SUCCESS == check
		; JumpSpaces(&runner)) 
	{	
		temp = *runner;
		switch (CheckInput(*runner))
		{
		case OPERAND:
			check = AnalizeOperand(&runner, operands, operators, lut);
			break;
		case OPERATOR:
			check = AnalizeOperator(&runner
						, operands
						, operators
						, lut);
			break;
		default:
			check = SYNTAX_ERROR;
			break;
		}
		LAST_ELEMENT = temp;
	}

	if (SUCCESS == check)
	{
		check = FinishOperation(operands, operators, _result, lut);
	}

	return check;
}

static void JumpSpaces(char **runner)
{
	while (' ' == **runner)
	{
		++(*runner);
	}
}

static elem_check_t CheckInput(char element)
{
	if (IsOperand(element))
	{
		return OPERAND;
	}
	else if (IsOperator(element))
	{
		return OPERATOR;
	}

	return INVALID;
}

static calc_status_t FinishOperation(
	stack_t *operands, 
	stack_t *operators, 
	double *_result, 
	operation_t lut[]
)
{
	calc_status_t check = SUCCESS;
	operand_t *result = NULL;

	while (SUCCESS == check && StackSize(operands) > 1)
	{
		check = PerformOperation(operands, operators, lut);
	}

	if (StackSize(operators) > 1 || StackSize(operands) > 1)
	{
		return (SUCCESS == check) ? SYNTAX_ERROR : check;
	}

	result = (operand_t *)StackPeek(operands);
	*_result = result->num;

	free(result);
	result = NULL;

	free(StackPeek(operators));

	return check;
}

/*****************************************************************************/

static calc_status_t AnalizeOperand(
	char **runner, 
	stack_t *operands,
	stack_t *operators,
	operation_t lut[]
)
{
	operand_t *operand = (operand_t *)malloc(sizeof(operand_t));
	if (NULL == operand)
	{
		return SYS_ERROR;
	}

	operand->num = LexAndParseOperand(runner);

	StackPush(operands, operand);

	CheckForUnary(operators, operands, lut);

	return SUCCESS;
}

static double LexAndParseOperand(char **runner)
{
	char *start = *runner;
	double curr_digit = 1;
	double result = 0;
		
	for (++(*runner)
		; IsOperand(**runner)
		; ++(*runner), curr_digit *= 10)
	{}

	for (*runner = start
		; IsOperand(**runner)
		; JumpDot(runner), curr_digit /= 10)
	{
		result += curr_digit * (**runner - 48);
	}

	return result;
}

static void JumpDot(char **runner)
{
	*runner += 1 + IsDot(*(*runner + 1));
}

static void CheckForUnary(
	stack_t *operators, 
	stack_t *operands, 
	operation_t lut[]
)
{
	operand_t *operand = (operand_t *)StackPeek(operands);
	operator_t *operator = (operator_t *)StackPeek(operators);
	while (ON == operator->unary_status)
	{		
		operand->num = lut[operator->operator].operation(0, operand->num);

		free(operator);	
		operator = NULL;
		StackPop(operators);

		operator = (operator_t *)StackPeek(operators);
	}
}

/*****************************************************************************/

static calc_status_t AnalizeOperator(
		char **runner, 
		stack_t *operands, 
		stack_t *operators, 
		operation_t lut[]
)
{
	calc_status_t check = SUCCESS;
	operator_t *top = NULL;

	CHECK_PARENTHESES += IsParentheses(**runner);

	if (IsCloseParentheses(**runner) && ParenthesesNotOpened())
	{
		return SYNTAX_ERROR;
	}

	/*************************************************/

	for (top = (operator_t *)StackPeek(operators)
		; SUCCESS == check
			&& StackSize(operands) > 1
			&& !IsOpenParentheses(top->operator)
			&& !IsUnaryOperator(**runner)
			&& !IsHigherPriority(**runner, top->operator, lut)
		; top = (operator_t *)StackPeek(operators))
	{
		check = PerformOperation(operands, operators, lut);
	}

	if (IsCloseParentheses(**runner) && IsOpenParentheses(top->operator))
	{
		free(top);
		top = NULL;
		StackPop(operators);

		CheckForUnary(operators, operands, lut);
	}

	/*************************************************/

	if (!IsCloseParentheses(**runner))
	{
		check = PushToStack(operators, **runner);
	}

	++(*runner);

	if (IsEndOfInput(**runner) && ParenthesesNotClosed())
	{
		return SYNTAX_ERROR;
	}

	return check;
}

static calc_status_t PushToStack(stack_t *operators, char element)
{
	operator_t *operator = (operator_t *)malloc(sizeof(operator_t));
	if (NULL == operator)
	{
		return SYS_ERROR;
	}

	operator->operator = element;
	operator->unary_status = OFF;
	if (IsUnaryOperator(element))
	{
		operator->unary_status = ON;
	}

	StackPush(operators, operator);

	return SUCCESS;
}

/*****************************************************************************/

static calc_status_t PerformOperation(
	stack_t *operands, 
	stack_t *operators, 
	operation_t lut[]
)
{
	operator_t *operator = NULL;
	operand_t *top_operand = NULL;
	operand_t *result = NULL;

	if (IsMathError(operands, operators))
	{
		return MATH_ERROR;
	}

	operator = (operator_t *)StackPeek(operators);
	top_operand = (operand_t *)StackPeek(operands);
	StackPop(operands);
	result = (operand_t *)StackPeek(operands);

	result->num = lut[operator->operator].operation(result->num, top_operand->num);

	free(operator);
	operator = NULL;
	StackPop(operators);

	free(top_operand);
	top_operand = NULL;

	return SUCCESS;
}

/*****************************************************************************/
