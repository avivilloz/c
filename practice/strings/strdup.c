/*****************************************************************************
* title: strdup
* author: aviv illoz
* description: duplicates a string
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strdup */
#include <stdlib.h> /* malloc */

char *strdup(const char *s);

char *Strdup(const char *s)
{
	char *new_s = malloc(strlen(s) + 1);
	int i = 0;

	for (; *s; s++, i++)
	{
		*(new_s + i) = *s;
	}

	*(new_s + i) = '\0';

	return new_s;
}

int main(void) 
{
	const char *str = "Hi my name is Borat"; 

	char *hey = strdup(str);

	char *yow = Strdup(str);

	printf("%s, %p\n", str, str);

	printf("%s, %p\n", hey, hey);

	printf("%s, %p\n", yow, yow);	

	free(hey);

	free(yow);

	return 0;
}
