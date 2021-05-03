/*****************************************************************************
* title: strchr
* author: aviv illoz
* description: searches for a certain char in a string
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strchr */

char *Strchr(const char *s, int c)
{
	while (c != *s && *s)
	{
		++s;
	}

	if (c != *s) 
	{
		return NULL; 
	}

	return (char*) s;
}

int main(void) 
{
	const char *str = "Hi my name is Borat"; 
	int letter = 'c';

	if (strchr(str, letter) == Strchr(str, letter))
	{
		printf("You succeeded\n");
	}
	else
	{
		printf("NOT\n");
	}

	return 0;
}
