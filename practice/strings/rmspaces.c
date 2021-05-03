/*****************************************************************************
* title: remove spaces
* author: aviv illoz
* description: remove spaces in the beginning and end of a string, and also if 
* repeated in the middle
******************************************************************************/

#include <stdio.h> /* printf */

void RmSpaces(char *str)
{
	char *temp = str;
	
	for (; '\0' != *str; str++)
	{	
		if (' ' == *str || '\t' == *str)
		{
			while (str == temp && (' ' == *str || '\t' == *str)) 
			{
				int i = 0;
				for (; *(str + i); i++)
				{
					*(str + i) = *(str + i + 1);
				}
			}
			
			str++;

			while ((' ' == *str || '\t' == *str))
			{
				int i = 0;
				for (; *(str + i); i++)
				{
					*(str + i) = *(str + i + 1);
				}
			}
		}
	}
}

int main(void) 
{
	char a[50] = "			ola    sou      o     gabriel";
	
	RmSpaces(a);

	printf("%s\n", a);

	return 0;
}
