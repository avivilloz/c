/*****************************************************************************
* title: strncopy
* author: aviv illoz
* description: copies specific amount of chars from a string to another empty 
* string with allocated memory
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strncpy */
#include <stdlib.h> /* malloc */

char *Strncpy(char *dest, const char *src, size_t n)
{
	unsigned int i = 0;
	char *runner = dest;

	for (; i < n; src++, i++)
	{
		*runner = *src;
	}

	return dest;
}

int main(void) 
{
	const char *str = "Hi my name is Borat"; 
	char *str2 = malloc(50 * sizeof(char));

	if (strncpy(str2, str, 25) == Strncpy(str2, str, 25))
	{
		printf("You succeeded\n");
	}
	else
	{
		printf("NOT\n");
	}

	free(str2);

	return 0;
}
