/*****************************************************************************
* title: Atoi
* author: aviv illoz
* description: Transforms strings into integers
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int Atoi(char *str)
{
	int i = 0, j = 0, check = 1, n = 0;

	for (; '\0' != str[i]; ++i)
	{
		check *= 10;
	}

	for (; j < i; ++j)
	{
		check /= 10;
		n += ((str[j] - 48) * check);
	}

	return n;
}

int main(void)
{
	char *str = "852369";

	int n  = Atoi(str);

	printf("%d\n%s\n", n, str);

	return 0;
}
