/*****************************************************************************
* title: strcpy
* author: aviv illoz
* description: copies a whole string to another empty string with allocated 
* memory
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strcpy */
#include <stdlib.h> /* malloc */

char *Strcpy(char *string1, const char *string2)
{
	char *start = string1;

	for (; '\0' != *string2; string2++, string1++)
	{
		*string1 = *string2;
	}

	return start;

}

int main(void) 
{
	const char *str = "Hi my name is Borat"; 
	char *str2 = malloc(50 * sizeof(char));  

	if (strcpy(str2, str) == Strcpy(str2, str))
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
