/*****************************************************************************
* title: strstr
* author: aviv illoz
* description: finds substrings within strings
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strstr */

char *Strstr(const char *haystack, const char *needle)
{
	size_t i = 0;
	size_t needle_size = strlen(needle);

	while ('\0' != *haystack)
	{
		while (*haystack != *needle && '\0' != *haystack)
		{
			++haystack;
		} 

		while (i < needle_size && *(haystack + i) == *(needle + i) && '\0' != *(haystack + i))
		{
			i++;
		}

		if (needle_size == i)
		{
			return (char*) haystack;
		}
		else if ('\0' != *haystack)
		{
			haystack++;
		}
	}

	return NULL;
}

int main(void) 
{
	const char *str = "Hi my name is Borat";
	const char *str2 = "hello";

	if (strstr(str, str2) == Strstr(str, str2))
	{
		printf("You succeeded\n");
	}
	else
	{
		printf("NOT\n");
	}

	return 0;
}
