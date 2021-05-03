/*****************************************************************************
* title: Memcpy
* author: aviv illoz
* description: copies memory without overlapping
******************************************************************************/

#include <stdio.h>
#include <string.h>

void *Memcpy(void *dest, const void *src, size_t bytes)
{
	unsigned int word = sizeof(size_t);
	char *runner = dest;
	const char *runner2 = src;

	for (; bytes >= word; bytes -= word, runner += word, runner2 += word)
	{
		*(size_t *)runner = *(size_t *)runner2;
	}
	
	for (; bytes > 0; --bytes, ++runner, ++runner2)
	{
		*runner = *runner2;
	}

	return dest;
}

int main(void)
{
	int i = 0;
	char str1[70] = "Hello World";
	char str2[70];
	int arr1[70];
	int arr2[70] = {5,4,3,2,1};

	printf("Memcpy test:\n\n");

	Memcpy(str2, str1, 11*sizeof(char));

	Memcpy(arr1 + 1, arr2, 17*sizeof(int));

	printf("%s\n", str2);

	for (; i < 5; ++i)
	{
		printf("%d ", arr1[i]);
	}

	printf("\n");

	for (i = 0; i < 5; ++i)
	{
		printf("%d ", arr2[i]);
	}

	printf("\n\n");

	printf("memcpy test:\n\n");

	memcpy(str2, str1, 11*sizeof(char));

	memcpy(arr1 + 1, arr2, 17*sizeof(int));

	printf("%s\n", str2);

	for (i = 0; i < 5; ++i)
	{
		printf("%d ", arr1[i]);
	}

	printf("\n");

	for (i = 0; i < 5; ++i)
	{
		printf("%d ", arr2[i]);
	}

	printf("\n");

	return 0;
}
