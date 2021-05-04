/****************************************************************************
Title: Memory Management
Author:	Aviv Illoz
Description: Fixed size memory allocator
*****************************************************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, free */

#include "fsa.h"	/* api */

#define NUMBER_BLOCKS 50
#define BLOCK_SIZE 50

int main(void)
{
	size_t memory_space_size = FSASuggestSize(NUMBER_BLOCKS, BLOCK_SIZE);
	size_t i = 0;
	void *buffer = malloc(memory_space_size);
	void *ptr_buffer[NUMBER_BLOCKS];
	fsa_t *memory_space = FSAInit(buffer, memory_space_size, BLOCK_SIZE);

	printf("free space: %lu\n", FSACountFree(memory_space));

	printf("************************ FSAAlloc ************************\n");
	for (; i < NUMBER_BLOCKS; ++i)
	{
		ptr_buffer[i] = FSAAlloc(memory_space);
		printf("free space: %lu\n", FSACountFree(memory_space));
		printf("**************** %p\n", ptr_buffer[i]);
	}

	printf("************************ FSAFree ************************\n");
	for (i = 0; i < NUMBER_BLOCKS; ++i)
	{
		FSAFree(ptr_buffer[i]);
		printf("free space: %lu\n", FSACountFree(memory_space));
	}

	free(buffer);
	
	return 0;
}
