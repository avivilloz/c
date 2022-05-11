/*****************************************************************************
* title: large numbs
* author: aviv illoz
* description: It receives to strings with numbers, adds the two numbers, 
* and returns value in string. Usefull for large numbers that don't fit in int 
* data types. 
******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* strlen */
#include <stdlib.h> /* malloc */

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

char *LargeNumbs(char *str_num1, char *str_num2)
{
	int i = strlen(str_num1) - 1, j = strlen(str_num2) - 1, k = 0;
	int n = 0;
	int size = (strlen(str_num1) >= strlen(str_num2)) ? 
		(strlen(str_num1)) + 1 : (strlen(str_num2)) + 1;
	char *result = malloc(size * sizeof(char));	

	for (; k < size; i--, j--, k++)
	{
		n /= 10;	
		n += ((i < 0) ? 0 : (*(str_num1 + i) - 48)) + ((j < 0) ? 0 : (*(str_num2 + j) - 48));		

		if (i < 0 && j < 0 && 0 == n)
		{
			*(result + k) = '\0';
			break;
		}
		
		*(result + k) = (n % 10) + 48;
	}

	RevStrOrd(result, k);

	return result;
}

int main(void)
{
	char *str_num1 = "946113616151591154554";
	char *str_num2 = "3616166116126621611";
	char *result = LargeNumbs(str_num1, str_num2);

	printf("result is %s\n", result);

	free(result);

	return 0;
}
