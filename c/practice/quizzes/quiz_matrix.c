/*****************************************************************************
Title: quiz_matrix 
Description: learn quiz_matrix
******************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

/*****************************************************************************/

long *Matrix(int **A, size_t columns, size_t rows)
{
	size_t i = 0, j = 0;
	size_t curr_columns = 0, curr_rows = 0;
	size_t size = rows * columns;
	size_t curr_matrix_size = 0;
	long *B = NULL;
	
	B = (long *)calloc(size, sizeof(long));
	if (NULL == B)
	{
		return NULL;
	}

	for (; i < size; ++i)
	{
		curr_columns = (i % columns) + 1;
		curr_rows = (i / columns) + 1;
		curr_matrix_size = curr_rows * curr_columns;
		for (j = 0; j < curr_matrix_size; ++j)
		{
			B[i] += A[j / curr_columns][j % curr_columns]; 
		}
	}

	return B;
}

int main(void)
{
	size_t i = 0, j = 0;
	int **A = NULL;
	long *B = NULL;
	
	A = (int **)malloc(sizeof(int *) * 8);
	if (NULL == A)
	{
		return 1;
	}

	for (; i < 8; ++i)
	{
		A[i] = (int *)malloc(sizeof(int) * 8);
		if (NULL == A[i])
		{
			return 1;
		}
	}

	for (i = 0; i < 8; ++i)
	{
		for (j = 0; j < 8; ++j)
		{
			A[i][j] = (i * 8) + j;
		}
	}

	B = Matrix(A, 8, 8);
	if (NULL == B)
	{
		return 1;
	}

	for (i = 0; i < 8 * 8; ++i)
	{
		if (0 == (i % 8))
		{
			puts("");
		}
		printf("%ld ", B[i]);
	}
	puts("");
	puts("");

	free(B);
	B = NULL;

	return 0;
}

/*****************************************************************************/

