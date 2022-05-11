/*****************************************************************************
* title: AtoiBases
* author: aviv illoz
* description: Transforms strings into integers in any base
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int AtoiBases(char *str, int base)
{
	int i = 0, j = 0, new_digit = 0, check = 1, n = 0;

	for (; '\0' != str[i]; ++i)
	{
		check *= base;
	}

	for (; j < i; ++j)
	{	
		check /= base;

		if (base > 10 && str[j] >= 65 && str[j] <= 90)
		{
			new_digit = (str[j] - 55) * check;
		}
		else if (base > 10 && str[j] >= 97 && str[j] <= 122)
		{
			new_digit = (str[j] - 87) * check;
		}
		else if (str[j] >= 48 && str[j] <= 57)
		{
			new_digit = (str[j] - 48) * check;
		}
	
		n += new_digit;
	}

	return n;
}

int main(void)
{
	char *str = "852369";

	char *str2 = "2f"; /*47*/

	char *str3 = "101"; /*5*/

	int n = AtoiBases(str, 10);

	int n2 = AtoiBases(str2, 16);

	int n3 = AtoiBases(str3, 2);

	printf("%d\n%s\n", n, str);
	
	printf("%d\n%s\n", n2, str2);

	printf("%d\n%s\n", n3, str3);

	return 0;
}
