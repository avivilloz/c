/*****************************************************************************
Title: Knight Tour
Author: Aviv Illoz
Description: Knight Tour API
******************************************************************************/

#include <stdio.h>	/* file management funcitons */

#include "knight.h"	/* api */

/*****************************************************************************/

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

/*****************************************************************************/

static char positions[BOARD_SIZE][DIRECTIONS];

/*****************************************************************************/

static void InitLut(void);
static void InitHelperLut(char rows[], char columns[], char directions[]);
static int CheckPosition(
	int position, 
	int direction, 
	char rows[], 
	char columns[], 
	char directions[]
);
static int IsOutside(
	int position, 
	direction_t direction, 
	char rows[], 
	char columns[]
);
static void CopyToFile(void);

/*****************************************************************************/

int main(void)
{
	InitLut();

	return 0;
}

/*****************************************************************************/

static void InitLut(void)
{
	int position = 0, direction = 0, i = 0, j = 0, k = 0;
	char rows[DIRECTIONS], columns[DIRECTIONS], directions[DIRECTIONS];

	InitHelperLut(rows, columns, directions);

	for (; position < BOARD_SIZE; ++position)
	{
		for (i = TOP_LEFT, j = 0, k = DIRECTIONS - 1; END != i; ++i)
		{
			direction = CheckPosition(position, i, rows, columns, directions); 
			if (OUT_OF_BOUNDARY == direction)
			{
				positions[position][k] = OUT_OF_BOUNDARY;
				--k;
			}
			else
			{
				positions[position][j] = direction;
				++j;
			}
		}
	} 

	CopyToFile();
}

static void InitHelperLut(char rows[], char columns[], char directions[])
{
	rows[TOP_LEFT] = -2;
	rows[TOP_RIGHT] = -2;
	rows[RIGHT_TOP] = -1;
	rows[RIGHT_BOTTOM] = 1;
	rows[BOTTOM_RIGHT] = 2;
	rows[BOTTOM_LEFT] = 2;
	rows[LEFT_BOTTOM] = 1;
	rows[LEFT_TOP] = -1;

	columns[TOP_LEFT] = -1;
	columns[TOP_RIGHT] = 1;
	columns[RIGHT_TOP] = 2;
	columns[RIGHT_BOTTOM] = 2;
	columns[BOTTOM_RIGHT] = 1;
	columns[BOTTOM_LEFT] = -1;
	columns[LEFT_BOTTOM] = -2;
	columns[LEFT_TOP] = -2;

	directions[TOP_LEFT] = (BOARD_LEN * -2) - 1;
	directions[TOP_RIGHT] = (BOARD_LEN * -2) + 1;
	directions[RIGHT_TOP] = -BOARD_LEN + 2;
	directions[RIGHT_BOTTOM] = BOARD_LEN + 2;
	directions[BOTTOM_RIGHT] = (BOARD_LEN * 2) + 1;
	directions[BOTTOM_LEFT] = (BOARD_LEN * 2) - 1;
	directions[LEFT_BOTTOM] = BOARD_LEN - 2;
	directions[LEFT_TOP] = -BOARD_LEN - 2;
}

static int CheckPosition(
	int position, 
	int direction, 
	char rows[], 
	char columns[], 
	char directions[]
)
{
	if (IsOutside(position, direction, rows, columns))
	{
		return OUT_OF_BOUNDARY;
	}
	else
	{
		return position + directions[direction];
	}
}

static int IsOutside(
	int position, 
	direction_t direction, 
	char rows[], 
	char columns[]
)
{
	int new_row = (position / BOARD_LEN) + rows[direction];
	int new_column = (position % BOARD_LEN) + columns[direction];

	return (new_row < 0) || (new_row >= BOARD_LEN) || 
		   (new_column < 0) || (new_column >= BOARD_LEN);		
}

static void CopyToFile(void)
{
	FILE *fp = fopen("/home/avivilloz/git/ds/knight/include/lut.h", "a");
	size_t i = 0, j = 0;

	fputs("#include \"knight.h\"\n\n", fp);
	fputs("const int positions[BOARD_SIZE][BOARD_LEN] =\n{\n", fp);

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		fputs("\t{", fp);
		for (j = 0; j < DIRECTIONS - 1; ++j)
		{
			fprintf(fp, "%d", positions[i][j]);
			fputs(", ", fp);
		}
		fprintf(fp, "%d", positions[i][j]);
		if (BOARD_SIZE - 1 != i)
		{
			fputs("},\n", fp);
		}
	}
	fputs("}\n};", fp);

	fclose(fp);
}

/*****************************************************************************/
