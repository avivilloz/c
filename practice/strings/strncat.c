/*****************************************************************************
* title: strncat
* author: aviv illoz
* description: adds specific amount of chars from one string to the other, 
* not overlaping it. 
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strncat */

char *Strncat(char *dest, const char *src, size_t n)
{
	char *runner = dest;
	size_t i = 0;
	
	while ('\0' != *runner)
	{
		runner++;
	}
	
	for(; i < n && '\0' != *(src + i); src++, runner++, i++) 
	{
		*runner = *src; 
	}
	*(runner + 1) = '\0';

	return dest; 
}

int main(void) 
{
	char str[50] = "Hi my name is Borat";
	const char str2[] = " , I am from Israel";
	size_t n = 5;
  	
	if (strncat(str, str2, n) == Strncat(str, str2, n))
	{
		printf("You succeeded\n");
	}
	else
	{
		printf("NOT\n");
	}

	return 0;
}
