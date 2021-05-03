#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *RevStrInLowCase(char *str)
{
	int size = strlen(str) - 1, middle = size / 2 + 1, i = 0, temp = 0;	

	char *dest = malloc(size * sizeof(char));

	for (; i < middle; i++)
	{		

		temp = (isupper(str[i])) ? str[i] + 32 : str[i];

		dest[i] = (isupper(str[size - i])) ? str[size - i] + 32 : str[size - i];

		dest[size - i] = temp;
	}

	return dest;
}

int main(void)
{
	char *str = "oI mEus AmiGos";

	str = RevStrInLowCase(str);

	printf("%s\n", str);

	return 0;
}
