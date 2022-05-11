/*****************************************************************************
* title: strcasecmp
* author: aviv illoz
* description: compares to strings, and it is case sensitive. 
******************************************************************************/

#include <stdio.h> /* printf */
#include <strings.h> /* strcasecmp */

int Strcasecmp(char *string1, const char *string2)
{
	for (; '\0' != *string1; string1++, string2++)
	{
		if (*string1 != *string2 && *string1 + 32 != *string2 && *string1 - 32 != *string2)
		{
			break;
		}
	}

	return (*string1 - *string2);
}

int main(void) 
{
	const char *str = "Hi my name is Borat"; 
	char *str2 = "Hi My name is Borat";

	if (strcasecmp(str2, str) == Strcasecmp(str2, str))
	{
		printf("You succeeded\n");
	}
	else
	{
		printf("NOT\n");
	}

	return 0;
}
