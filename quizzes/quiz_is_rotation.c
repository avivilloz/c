#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*checks if str2 is rotaiton of str1*/
int IsRotation(char *str1, char* str2)
{
	int size = strlen(str2);

	char *temp = malloc(size * sizeof(int));

	int i = 0, j = 0, k = 0;

	char first_char = '\0';

	for (; i < size; i++)
	{
		temp[i] = str2[i];
	}
	
	for (i = 0; i < size; i++)
	{	
		for (j = 0; str1[j] == temp[j] && j < size; j++)
		{}

		if (j == size)
		{
			printf("Is Rotation\n");
			return 0;
		}
			
		k = 0;

		first_char = temp[k];
		for (; k < size; k++)
		{
			if ((size - 1) == k)
			{
				temp[k] = first_char;
			}
			else
			{
				temp[k] = temp[k + 1];
			}
		}
	}
		
	printf("Is not Rotation\n");
	return 1;
}

int main(void)
{
	char *str1 = "2311";

	char *str2 = "1123";
	
	printf("%d\n", IsRotation(str1, str2));

	return 0;
}
