/*****************************************************************************
* title: strcmp
* author: aviv illoz
* description: compares two strings, not case sensitive
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */

int Strcmp(char *string1, const char *string2)
{
	for (; '\0' != *string1; string1++, string2++)
	{
		if (*string1 != *string2)
		{
			break;
		}
	}

	return (*string1 - *string2);
}

int main(void) 
{
	const char *str = "Hi my name is Borat"; 
	char *str2 = "Hello my name is Borat";

	if (strcmp(str2, str) == Strcmp(str2, str))
	{
		printf("You succeeded\n");
	}
	else
	{
		printf("NOT\n");
	}

	return 0;
}
