/****************************************************************************
Title: Calculator
Author: Aviv Illoz
Description: Calculator API
*****************************************************************************/

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

typedef enum {SUCCESS, SYS_ERROR, MATH_ERROR, SYNTAX_ERROR} calc_status_t;

/*****************************************************************************/
/*
DESCRIPTION:
        Function recieves a string 'input', performs calculations accordingly
        and puts the result in '_result'. 

RETURN VALUE:
        On success returns 'SUCCESS'.

ERRORS:
        SYS_ERROR - allocation failed, overflow or underflow occurred.

        MATH_ERROR - division by zero.

        SYNTAX_ERROR - the 'input' contains opening brackets without closing
        them, several decimal points in one number, a character which is
        different from {0 - 9, (, )} and operations {'-', '+', '*', '/', '^'}.
        Or it doesn't contain any operations but just numbers and vice versa.
        Or the order of operations and other charecters is not correct.
*/

calc_status_t Calculator(const char *input, double *_result);

#endif /*__CALCULATOR_H__*/
