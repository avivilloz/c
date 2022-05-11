/*****************************************************************************
* title: Memset
* author: aviv illoz
* description: adds value to a certain number of memory bytes
******************************************************************************/

#include <stdio.h>
#include <string.h>

void *Memset(void *s, int c, size_t bytes)
{
	unsigned int word = sizeof(size_t);
	unsigned int counterbytes = 1;
	char *runner = s;
	size_t temp = c;
	size_t big_c = temp;

	for (; counterbytes < word; ++counterbytes)
	{
		temp <<= 8;
	
		big_c |= temp;
	}

	for (; bytes >= word; bytes -= word, runner += word)
	{
		*(size_t *)runner = big_c;
	}
	
	for (; bytes > 0; --bytes, ++runner)
	{
		*runner = c;
	}

	return s;
}

int main(void)
{
	int i = 0;

	char str[70] = "Hello World";

	int arr[70] = {1,2,3,4,5};

	printf("Memset test:\n\n");

	Memset(str + 1, '.', 50*sizeof(char));

	Memset(arr + 1, 10, 15*sizeof(int));

	printf("%s\n", str);

	for (; i < 5; ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n\n");

	printf("memset test:\n\n");

	memset(str + 1, '.', 50*sizeof(char));

	memset(arr + 1, 10, 15*sizeof(int));

	printf("%s\n", str);

	for (i = 0; i < 5; ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");

	return 0;
}
