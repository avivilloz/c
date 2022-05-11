/*****************************************************************************
* title: 3 char arrays
* author: aviv illoz
* description: compare 3 strings, and it checks if there are equal chars in 
* the first 2 strings that are not in the 3rd string
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *CharArrays(char *str1, char *str2, char *str3)
{
	int i1 = strlen(str1), i2 = strlen(str2), i3 = strlen(str3), j1 = 0, j2 = 0, j3 = 0; 

	int size = 1, k = 0;

	char *result = malloc(size);

	char *temp = NULL;

	for (; j1 < i1; ++j1)
	{
		for (k = 0; k < size - 1; ++k)
		{
			if (str1[j1] == result[k])
			{
				goto end;
			}	
		}
		for (j2 = 0; j2 < i2; ++j2)
		{
			for (j3 = 0; j3 < i3 && str1[j1] == str2[j2]; ++j3)
			{
				if (str1[j1] == str3[j3])
				{
					goto end;
				}
				if (j3 == i3 - 1)
				{
					++size;

					temp = realloc(result, size);

					if (NULL == temp)
					{
						exit(0);
					}

					result = temp;

					temp = NULL;

					result[size - 2] = str1[j1];
		
					goto end;
				}
			}	
		}
		end:;
	}	

	result[size - 1] = '\0';

	return result;
}

int main (void)
{
	char *str1 = "abdcea";

	char *str2 = "adea";

	char *str3 = "fghjk";

	char *result = CharArrays(str1, str2, str3);

	printf("%s\n", result);

	free(result);

	return 0;
}
