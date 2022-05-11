#include <stdio.h>
#include <string.h>

/*
->basic implementation

static int IsPalindrome(char *str)
{
	size_t i = 0, j = strlen(str) - 1, mid = (j + 1) / 2;

	for (; i < mid && j > mid; ++i, --j)
	{
		if (str[i] != str[j])
		{
			return 0;
		}
	}

	return 1;
}
*/

/*->recursion*/

static int CompareStrs(char *str_from_start, char *str_from_end);

static int IsPalindrome(char *str)
{
	char *str_end = str + (strlen(str) - 1);
	
	return CompareStrs(str, str_end);
}

static int CompareStrs(char *str_from_start, char *str_from_end)
{
	if ('\0' == *str_from_start)
	{
		return 1;
	}

	if (*str_from_start != *str_from_end)
	{
		return 0;
	}

	return CompareStrs(str_from_start + 1, str_from_end - 1);	
}

int main(void)
{
	char *palindrome = "hannah";
	char *not_palindrome = "asasasaafag";

	printf("palindrome: %d\n", IsPalindrome(palindrome));
	printf("not_palindrome: %d\n", IsPalindrome(not_palindrome));

	return 0;
}
