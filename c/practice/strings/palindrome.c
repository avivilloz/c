/*****************************************************************************
* title: palindrome
* author: aviv illoz
* description: it tells the user if his string is palindrome.
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strlen */

int IsPalindrome(const char *str)
{
	int middle = strlen(str)/2;
	int end = strlen(str) - 1;
	int i = 0;
	
	while (i != middle && *(str + i) == *(str + end - i))
	{
		i++;
		if (i == middle)
		{
			return 0;
		}
	}

	return 1;
}

int main(void)
{
	const char *str = "hnah";
 
	printf("%d\n", IsPalindrome(str));

	return 0;
}
