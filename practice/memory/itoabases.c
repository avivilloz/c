/*****************************************************************************
* title: ItoaBases
* author: aviv illoz
* description: Transforms intgers into strings (it works with any base integer)
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void RevStrOrd(char *str, int size)
{
	int i = 0, j = size - 1, k = size / 2;

	for (; i < k; j--, i++)
	{
		int temp = *(str + i);
		*(str + i) = *(str + j);
		*(str + j) = temp;
	}
}

char *ItoaBases(int n, int base)
{
	int i = 0, new_digit = 0, temp = n;

	char *str = NULL;

	for (; temp > 0; temp /= base, ++i)
	{}
		
	str = malloc(i + 1);

	for (i = 0; n > 0; n /= base, ++i)
	{	
		new_digit = n % base;
	
		if (base > 10 && new_digit >= 10)
		{
			new_digit += 55;
		}
		else if (new_digit < 10)
		{
			new_digit += 48;
		}
		
		str[i] = new_digit; 
	}

	str[i] = '\0';

	RevStrOrd(str, i);

	return str;
}

int main(void)
{
	int n = 852369;

	int n2 = 100;

	int n3 = 5;

	char *str = ItoaBases(n, 10);

	char *str2 = ItoaBases(n2, 16);

	char *str3 = ItoaBases(n3, 2);

	printf("%d\n%s\n", n, str);
	
	printf("%d\n%s\n", n2, str2);

	printf("%d\n%s\n", n3, str3);

	free(str);

	free(str2);
	
	free(str3);

	return 0;
}
