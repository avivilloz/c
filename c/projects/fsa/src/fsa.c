/****************************************************************************
Title: Memory Management
Author:	Aviv Illoz
Description: Fixed size memory allocator
*****************************************************************************/

#include <assert.h>	/* assert */

#include "fsa.h"	/* api */

#define WORD_SIZE sizeof(size_t)

struct fsa
{
	size_t first_free_offset;
	size_t free_blocks;
};

struct fsa_block
{
	size_t next_free_offset;
};

/*****************************************************************************/

static size_t BlockAlignment(size_t block_size)
{
	return block_size + (WORD_SIZE - (block_size % WORD_SIZE));
}

/*****************************************************************************/

size_t FSASuggestSize(size_t number_blocks, size_t block_size)
{
	return sizeof(fsa_t) 
		+ (sizeof(fsa_block_t) * number_blocks)
		+ (number_blocks * Alignment(block_size));
}


/*****************************************************************************/

fsa_t *FSAInit(void *buffer, size_t buffer_size, size_t block_size)
{
	/* declaring variables */
	char *runner = NULL;
	size_t i = 1
	, fsa_t_size = 0
	, fsa_block_t_size = 0
	, number_blocks = 0;

	assert(NULL != buffer);

	/* initializing variables */
	block_size = Alignment(block_size);
	fsa_t_size = sizeof(fsa_t);
	fsa_block_t_size = sizeof(fsa_block_t);
	number_blocks = (buffer_size - fsa_t_size) 
			/ (block_size + fsa_block_t_size);
	
	/* setting fsa to the beginning of buffer */
	((fsa_t *)buffer)->first_free_offset = fsa_t_size;
	((fsa_t *)buffer)->free_blocks = number_blocks;
	
	/* setting one fsa_block for each block in buffer */
	for (runner = (char *)buffer + fsa_t_size
		; i < number_blocks
		; ++i, runner += fsa_block_t_size + block_size)
	{
		((fsa_block_t *)runner)->next_free_offset = (i * block_size) 
						+ (i * fsa_block_t_size)
						+ fsa_t_size;
	}
	((fsa_block_t *)runner)->next_free_offset = 0;

	/* returning fsa, i.e first beginning of buffer */
	return (fsa_t *)buffer;
}


/*****************************************************************************/

void *FSAAlloc(fsa_t *allocator)
{
	/* declaring variables */
	char *runner = NULL;
	char *return_ptr = NULL;
	size_t temp = 0;

	assert(NULL != allocator);

	/* checking if my memory space has free spaces */
	if (0 == allocator->free_blocks)
	{
		return NULL;
	}

	/* initializing variables */
	runner = (char *)allocator + allocator->first_free_offset;
	return_ptr = runner + sizeof(fsa_block_t);
	temp = allocator->first_free_offset;

	/* setting new values for fsa_t struct and current fsa_block_t struct */
	allocator->first_free_offset = ((fsa_block_t *)runner)->next_free_offset;
	((fsa_block_t *)runner)->next_free_offset = temp;
	--allocator->free_blocks;

	/* return new allocated block as (void *) type */
	return (void *)return_ptr;
}

/*****************************************************************************/

void FSAFree(void *block)
{
	/* declaring variables */
	fsa_block_t *fsa_block_ptr = NULL;
	fsa_t *fsa_ptr = NULL;
	size_t temp = 0;

	assert(NULL != block);

	/* initializing variables */
	fsa_block_ptr = (fsa_block_t *)((char*)block - sizeof(fsa_block_t));
	fsa_ptr = (fsa_t *)((char *)fsa_block_ptr - fsa_block_ptr->next_free_offset);
	temp = fsa_ptr->first_free_offset;

	/* setting new values for fsa_t struct and current fsa_block_t struct */
	fsa_ptr->first_free_offset = fsa_block_ptr->next_free_offset;
	fsa_block_ptr->next_free_offset = temp;
	++fsa_ptr->free_blocks;
}


/*****************************************************************************/

size_t FSACountFree(const fsa_t *allocator)
{
	assert(NULL != allocator);

	return allocator->free_blocks;
}
