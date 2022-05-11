/*****************************************************************************
Title: Knight Tour
Author: Aviv Illoz
Description: Knight Tour API
******************************************************************************/

#include <stdio.h>		/* printf */
#include <time.h>		/* time */
#include <stdlib.h>		/* qsort */
#include <string.h>		/* memset */

#include "knight.h"		/* api */
#include "lut.h"		/* api */

/****************************************************************************/

#define FIVE_MINUTES (5 * 60)
#define DIRECTIONS 8
#define OUT_OF_BOUNDARY -1

typedef enum 
{
	TOP_LEFT = 0, 
	TOP_RIGHT, 
	RIGHT_TOP, 
	RIGHT_BOTTOM,
	BOTTOM_RIGHT, 
	BOTTOM_LEFT, 
	LEFT_BOTTOM, 
	LEFT_TOP,
	END
} direction_t;

typedef struct position
{
	int available_directions;
	int position;
} position_t;

/****************************************************************************/

static int GetPosition(int row, int column);
static status_t FindPath(
	char board[], 
	int position, 
	int steps[BOARD_SIZE], 
	int step,
	clock_t tic
);
static void SetBusy(char board[], int position);
static int IsAvailable(char board[], int position);
static int InitAvailablePositions(
	char board[], 
	position_t buffer[], 
	int position
);
static int IsBefore(const void *lhs, const void *rhs);
static int IsEndOfBoard(int step);
static int IsEndOfTime(clock_t tic);

/***************************** FUNCTIONS *************************************/

status_t KnightTour(
	int initial_row_position, 
	int initial_column_position, 
	int steps[BOARD_SIZE]
)
{
	int position = GetPosition(initial_row_position, initial_column_position);
	char board[BOARD_SIZE];
	clock_t tic = 0;

	memset(board, 0, BOARD_SIZE);

	tic = clock();

	return FindPath(board, position, steps, 1, tic);
}

static int GetPosition(int row, int column)
{
	return (row * BOARD_LEN) + column;
}

static status_t FindPath(
	char board[], 
	int position, 
	int steps[BOARD_SIZE], 
	int step,
	clock_t tic
)
{
	SetBusy(board, position);

	if (!IsEndOfBoard(step))
	{
		position_t buffer[DIRECTIONS];
		int i = 0, available_directions = 0;
		status_t status = FAILURE;

		available_directions = InitAvailablePositions(board, buffer, position);

		for (; i < available_directions && 
			 FAILURE == status && 
			 !IsEndOfTime(tic)
			 ; ++i)
		{
			status = FindPath(board, buffer[i].position, steps, step + 1, tic);
		}

		if (SUCCESS == status)
		{
			steps[position] = step;
		}

		return status;
	}

	steps[position] = step;

	return SUCCESS;
}

static int InitAvailablePositions(
	char board[], 
	position_t buffer[], 
	int position
)
{
	int i = 0, j = 0; 
	int buffer_length = 0;
	int available_directions = 0;
	int direction_position = positions[position][i];	

	for (; i < DIRECTIONS && -1 != direction_position
		 ; ++i, direction_position = positions[position][i])
	{
		if (IsAvailable(board, direction_position))
		{
			buffer[buffer_length].position = direction_position;

			for (j = 0, available_directions = 0
				 ; j < DIRECTIONS && 
				 -1 != positions[direction_position][j]
				 ; ++j)
			{
				if (IsAvailable(board, positions[direction_position][j]))
				{
					++available_directions;
				}
			}

			buffer[buffer_length].available_directions = available_directions;
			++buffer_length;
		}
	}

	qsort(buffer, buffer_length, sizeof(position_t), IsBefore);

	return buffer_length;
}

static int IsBefore(const void *lhs, const void *rhs)
{
	return (((position_t *)lhs)->available_directions 
			- ((position_t *)rhs)->available_directions);
}

static void SetBusy(char board[], int position)
{
	board[position] = 1;
}

static int IsAvailable(char board[], int position)
{
	return (0 == board[position]);
}

static int IsEndOfBoard(int step)
{
	return (BOARD_SIZE == step);
}

static int IsEndOfTime(clock_t tic)
{
	return ((clock() - tic) / CLOCKS_PER_SEC) >= FIVE_MINUTES;
}

/*****************************************************************************/

void PrintResultPath(int steps[BOARD_SIZE])
{
	int i = 0;

	for (; i < BOARD_SIZE; ++i)
	{
		if (0 != i && 0 == (i % BOARD_LEN))
		{
			printf("\n\n");
		}
		printf("%d   ", steps[i]);
	}
	printf("\n\n");
}

/****************************************************************************/
