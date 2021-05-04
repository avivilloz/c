/******************************************************************************
Title: Knight Tour
Author: Aviv Illoz
Description: Knight Tour API v2
*****************************************************************************/

#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__

#include <stddef.h> /* size_t */

/*****************************************************************************/

#define BOARD_LEN (8) /* do not change the name of the macro ! */

#define BOARD_SIZE (BOARD_LEN * BOARD_LEN)

/*****************************************************************************/

typedef enum
{
    SUCCESS = 0,
    FAILURE
} status_t; 

/*****************************************************************************/
/*
Description:        Gets a starting position of a knights on a chess board and tries
                    to find a path it can move while visit each position on the board
                    exactly one time
                    Each position is represents by two numbers [line, column]
Input:	            empty array (size 64 bits) will contain the knight's path. (out param)
                    initial row and initial column: coordinates point on the board where the 
                    knight will start
Output:		        If succeed, returns SUCCESS and updates result
	                If fails, returns FAILURE (In this case, result might include garbage value)
Error proccessing:  -
*/

status_t KnightTour(
	int initial_row_position, 
	int initial_column_position, 
	int result[BOARD_SIZE]
);

/*****************************************************************************/
/*
Description:        Helper function to print the final array with all positions of the knight
Input:	            final output result of the KnightTour function
Output:		        void
Error proccessing:  -
*/

void PrintResultPath(int result[BOARD_SIZE]);

/*****************************************************************************/

#endif /* __KNIGHT_TOUR_H__ */
