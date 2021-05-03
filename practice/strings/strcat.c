/*****************************************************************************
* title: strcat
* author: aviv illoz
* description: adds string to another string without overlaping it.
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strcat */

char *Strcat(char *dest, const char *src)
{
	char *runner = dest;
	
	while ('\0' != *runner)
	{
		runner++;
	}

	for (; *src; src++, runner++) 
	{
		*runner = *src; 
	}

	return dest; 
}

int main(void) 
{
	char str[80] = "Hi my name is Borat";
	const char str2[] = " , I am from Israel"; 	

	if (strcat(str, str2) == Strcat(str, str2))
	{
		printf("You succeeded\n");
	}
	else
	{
		printf("NOT\n");
	}

	return 0;
}
