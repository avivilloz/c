/*****************************************************************************
* title: Memmove
* author: aviv illoz
* description: copies memory also overlapping
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *Memmove(void *dest, const void *src, size_t bytes)
{
	char *runner1 = dest;

	const char *runner2 = src;

	/*copying byte by byte*/
	for (; bytes > 0; --bytes)
	{
		runner1[bytes - 1] = runner2[bytes - 1];
	}

	return dest;
}

/**************************TEST****************************/

int main(void)
{
	int i = 0;

	char str1[70] = "GeeksForGeeks";

	int arr1[70] = {1,2,3,4,5};

	int arr2[70] = {5,4,3,2,1};

/*comment out either original memmove or my memmove to test each*/
/******************************************************/

	printf("Memmove test:\n\n");

	Memmove(str1 + 5, str1, 8 * sizeof(char));

	Memmove(arr1 + 1, arr2, 3 * sizeof(int));

	printf("%s\n", str1);

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

/******************************************************/

	printf("memmove test:\n\n");

	memmove(str1 + 5, str1, 8 * sizeof(char));

	memmove(arr1 + 1, arr2, 3 * sizeof(int));

	printf("%s\n", str1);

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
