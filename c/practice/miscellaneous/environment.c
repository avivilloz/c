/*****************************************************************************
* title: Environment
* author: aviv illoz
* description: Copies all environment variables to a buffer in lowers case
******************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <ctype.h> /* isupper */

void CpyInLowCase(char *dest[], char *src[]);
char **CreateBuffer(char **src);
void PrintBuffer(char **buffer);
void FreeBuffer(char **buffer);

extern char **environ;

int main(void)
{	
	char **buffer = CreateBuffer(environ);
	CpyInLowCase(buffer, environ);	
	PrintBuffer(buffer);
	FreeBuffer(buffer);

	return 0;
}

char **CreateBuffer(char **src)
{
	int rows = 0, columns = 0, i = 0; 
	char **buffer = NULL;

	while (NULL != src[rows])
	{
		++rows;
	}

	buffer = (char **) malloc((rows + 1) * sizeof(char *)); 

	for (i = 0; i < rows; i++)
	{
		columns = strlen(src[i]) + 1;
        	buffer[i] = (char *) malloc(columns * sizeof(char)); 
	}

	if (NULL == *src)
	{
		FreeBuffer(src);
		return NULL;
	}

	return buffer;
}

void CpyInLowCase(char *dest[], char *src[])
{
	unsigned int i = 0, j = 0, rows = 0;
	
	while (NULL != src[rows]) 
	{
		++rows;
	}

	for (i = 0; i < rows; i++)
	{
		for (j = 0; src[i][j]; j++)
		{
			dest[i][j] = src[i][j];
			if (isupper(dest[i][j]))
			{
				dest[i][j] += 32;
			}
		}
		dest[i][j] = '\0';
	}
	dest[i] = NULL;
}

void PrintBuffer(char **buffer)
{
	char **runner = buffer;
	int i = 0;
	
	for (; NULL != *runner; runner++, i++)
	{
		printf("%d: %s\n", i, *runner);
	}
}

void FreeBuffer(char **buffer)
{
	int i = 0, rows = 0;

	while (NULL != buffer[rows])
	{
		++rows;
	}
	
    	for (i = 0; i < rows; i++)
	{ 
		free(buffer[i]);
	}

	free(buffer);
}
