/*****************************************************************************
* title: strlen
* author: aviv illoz
* description: checks length of string
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strlen */

size_t Strlen(const char *str)
{
	const char *start = str;
	
	while ('\0' != *str) 
	{
		++str;
	}

	return (str - start);
}

int main(void) 
{
	const char *str = "Hi my name is Borat"; 

	if (strlen(str) == Strlen(str))
	{
		printf("You succeeded\n");
	}
	else
	{
		printf("NOT\n");
	}

	return 0;
}
