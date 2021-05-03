/****************************************************************************
Title: Variable Size Allocator - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Miriam
Description: Variable Size memory Allocator
*****************************************************************************/

#include <assert.h>	/* assert */
#include "vsa.h"	/* api */
#define WORD_SIZE sizeof(size_t)
#define VSA_HEAD_SIZE sizeof(vsa_t)
#define VSA_BLOCK_HEADER_SIZE sizeof(vsa_block_header_t)

struct vsa
{
	size_t allocated_size;
};

struct vsa_block_header
{
	size_t block_size;
	#ifndef NDEBUG
	size_t magic_number;
	#endif
};

#ifndef NDEBUG
static const size_t MAGIC_NUMBER = 7;
#endif

/************************* GENERAL STATIC FUNCTIONS **************************/

static size_t CreateStartingIndex(void)
{
	return VSA_HEAD_SIZE;
}

static vsa_block_header_t *GetFirstBlockHeader(void *buffer)
{
	return (vsa_block_header_t *)((char *)buffer + VSA_HEAD_SIZE);
}

static size_t RunnerBlockSize(char *runner)
{
	return ((vsa_block_header_t *)runner)->block_size;
}

static size_t IncreaseIndex(size_t curr_index, size_t size)
{
	return curr_index + VSA_BLOCK_HEADER_SIZE + (size - (size % 2));
}

static char *NextBlockHeader(char *runner, size_t size)
{
	return runner + VSA_BLOCK_HEADER_SIZE + (size - (size % 2));
}

static size_t MergeBlock(size_t merged_blocks_sum, char *runner)
{
	return merged_blocks_sum + VSA_BLOCK_HEADER_SIZE + RunnerBlockSize(runner);
}

static int IsEndOfAllocator(size_t curr_index, vsa_t *allocator)
{
	return (curr_index >= allocator->allocated_size);
}

static int IsAllocated(char *runner)
{
	return (RunnerBlockSize(runner) % 2);
}

static int IsBigEnough(size_t merged_blocks_sum, size_t block_size)
{
	return (merged_blocks_sum >= block_size);
}

/*********************** INIT STATIC FUNCTIONS *******************************/

static size_t BufferAlignment(size_t buffer_size)
{
	return buffer_size - (buffer_size % WORD_SIZE);
}

static void SetAllocatedSize(void *buffer, size_t buffer_size)
{
	((vsa_t *)buffer)->allocated_size = buffer_size;
}

static size_t SetFirstBlockSize(size_t buffer_size)
{
	return buffer_size - VSA_HEAD_SIZE - VSA_BLOCK_HEADER_SIZE;
}

/************************ ALLOC STATIC FUNCTIONS *****************************/

static size_t BlockAlignment(size_t block_size)
{
	if (block_size % WORD_SIZE)
	{
		block_size += (WORD_SIZE - (block_size % WORD_SIZE));
	}
	return block_size;
}

static int IsEnoughForNewBlock(size_t merged_blocks_sum, size_t block_size)
{
	return (merged_blocks_sum - block_size >= VSA_BLOCK_HEADER_SIZE + WORD_SIZE);
}

static void SetAsAllocated(char *block_header, size_t block_size)
{
	((vsa_block_header_t *)block_header)->block_size = block_size + 1;
}

static void CreateBlockHeader(char *block_header
				, size_t merged_blocks_sum
				, size_t block_size)
{
	vsa_block_header_t *new_block_header = (vsa_block_header_t *)(block_header 
					+ VSA_BLOCK_HEADER_SIZE + block_size);
	size_t total_block_size = block_size + VSA_BLOCK_HEADER_SIZE;
	new_block_header->block_size = merged_blocks_sum - total_block_size;
}

#ifndef NDEBUG
static void SetMagicNumber(char *block_header)
{
	((vsa_block_header_t *)block_header)->magic_number = MAGIC_NUMBER;
}
#endif

static void *StartOfBlock(char *block_header)
{
	return (void *)(block_header + VSA_BLOCK_HEADER_SIZE);
}

/*********************** FREE STATIC FUNCTIONS *******************************/

static vsa_block_header_t *GetBlockHeader(void *block)
{
	return (vsa_block_header_t *)((char *)block - VSA_BLOCK_HEADER_SIZE);
}

static void SetFree(vsa_block_header_t *block_header)
{
	--block_header->block_size;
}

/*****************************************************************************/

vsa_t *VSAInit(void *buffer, size_t buffer_size)
{
	vsa_block_header_t *first_block_header = NULL;

	assert(NULL != buffer);
	
	buffer_size = BufferAlignment(buffer_size);
	first_block_header = GetFirstBlockHeader(buffer);

	SetAllocatedSize(buffer, buffer_size);
	first_block_header->block_size = SetFirstBlockSize(buffer_size);
	#ifndef NDEBUG
	first_block_header->magic_number = MAGIC_NUMBER;
	#endif

	return (vsa_t *)buffer;
}

/*****************************************************************************/

void *VSAAlloc(vsa_t *allocator, size_t block_size)
{
	size_t curr_index = 0;
	size_t merged_blocks_sum = 0;
	size_t runner_block_size = 0;
	char *block_header = NULL; 
	char *runner = NULL;

	assert(NULL != allocator);
	
	block_size = BlockAlignment(block_size);
	curr_index = CreateStartingIndex();
	block_header = (char *)GetFirstBlockHeader((void *)allocator);

	while (!IsEndOfAllocator(curr_index, allocator))
	{
		runner = block_header;
		runner_block_size = RunnerBlockSize(runner);
		merged_blocks_sum = runner_block_size;
		while (!IsEndOfAllocator(curr_index, allocator) 
			&& !IsAllocated(runner) 
			&& !IsBigEnough(merged_blocks_sum, block_size))
		{
			curr_index = IncreaseIndex(curr_index, runner_block_size);
			if (!IsEndOfAllocator(curr_index, allocator))
			{
				runner = NextBlockHeader(runner, runner_block_size);
				runner_block_size = RunnerBlockSize(runner);
				if (!IsAllocated(runner))
				{
					merged_blocks_sum = MergeBlock(
							merged_blocks_sum, runner);
				}
			}
		}

		if (!IsEndOfAllocator(curr_index, allocator))
		{
			if (!IsAllocated(runner))
			{
				if (IsEnoughForNewBlock(merged_blocks_sum, block_size))
				{
					SetAsAllocated(block_header, block_size);
					CreateBlockHeader(block_header
							, merged_blocks_sum
							, block_size);
				}
				else
				{
					SetAsAllocated(block_header, merged_blocks_sum);
				}
				#ifndef NDEBUG
				SetMagicNumber(block_header);
				#endif
				return StartOfBlock(block_header);
			}
			curr_index = IncreaseIndex(curr_index, merged_blocks_sum);
			block_header = NextBlockHeader(block_header, merged_blocks_sum);
		}
	}

	return NULL;
}

/*****************************************************************************/

void VSAFree(void *block)
{
	vsa_block_header_t *block_header = NULL;

	assert(NULL != block);

	block_header = GetBlockHeader(block);

	#ifndef NDEBUG
	assert(MAGIC_NUMBER == block_header->magic_number);
	#endif

	if (IsAllocated((char *)block_header))
	{
		SetFree(block_header);
	}
}

/*****************************************************************************/

size_t VSALargestChunkAvailable(const vsa_t *allocator)
{
	size_t curr_index = 0;
	size_t chunk = 0;
	size_t merged_blocks_sum = 0;
	size_t runner_block_size = 0;
	char *runner = NULL;

	assert(NULL != allocator);

	curr_index = CreateStartingIndex();
	runner = (char *)GetFirstBlockHeader((void *)allocator);

	while (!IsEndOfAllocator(curr_index, (vsa_t *)allocator))
	{
		runner_block_size = RunnerBlockSize(runner);
		if (!IsAllocated(runner))
		{
			merged_blocks_sum = runner_block_size;
			while (!IsEndOfAllocator(curr_index, (vsa_t *)allocator)
				&& !IsAllocated(runner))
			{
				curr_index = IncreaseIndex(curr_index, runner_block_size);
				if(!IsEndOfAllocator(curr_index, (vsa_t *)allocator))
				{
					runner = NextBlockHeader(runner, runner_block_size);
					runner_block_size = RunnerBlockSize(runner);
					if (!IsAllocated(runner))
					{
						merged_blocks_sum = MergeBlock(
							merged_blocks_sum, runner);
					}
				}
			}
		}

		if (merged_blocks_sum > chunk)
		{
			chunk = merged_blocks_sum;
		}
		merged_blocks_sum = 0;
		runner = NextBlockHeader(runner, runner_block_size);
		curr_index = IncreaseIndex(curr_index, runner_block_size);
	}

	return chunk;
}



