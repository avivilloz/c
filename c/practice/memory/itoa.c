/*****************************************************************************
* title: Itoa
* author: aviv illoz
* description: Transforms intgers into strings
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

char *Itoa(int n)
{
	int i = 0, j = 0, check = 1;

	char *str = NULL;

	while (check <= n)
	{
		check *= 10;
		++i;
	}

	str = malloc(i + 1);

	for (; i > 0; --i, ++j)
	{
		str[j] = ((n % check) / (check / 10)) + 48;
		
		check /= 10;
	}

	str[j] = '\0';

	return str;
}

int main(void)
{
	int n = 852369;

	char *str = Itoa(n);

	printf("%d\n%s\n", n, str);

	free(str);

	return 0;
}
