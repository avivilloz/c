/****************************************************************************
Title: Memory Management
Author: Aviv Illoz
Description: Fixed size memory allocator
*****************************************************************************/

#ifndef __FIXED_SIZE_MEM_ALLOC_H__
#define __FIXED_SIZE_MEM_ALLOC_H__

#include <stddef.h> 	/* size_t*/

typedef struct fsa fsa_t;
typedef struct fsa_block fsa_block_t;

/*****************************************************************************/
/*
Decription: Suggest size of fsa based on user input of number and size of blocks	
Input:	number of blocks and size of them.		
Output:	Suggested size 	
Error proccessing: 	-
*/
size_t FSASuggestSize(size_t number_blocks, size_t block_size);


/*****************************************************************************/
/*
Decription: Initialization of fsa
Input: pointer to buffer and block size
Output:	pointer to fsa	
Error proccessing: - 
*/
fsa_t *FSAInit(void *buffer , size_t buffer_size, size_t block_size);


/*****************************************************************************/
/*
Decription: Single fsa block allocation.		
Input: pointer to fsa allocator.
Output: Pointer to allocate memory and NULL if no free space available.
Error proccessing: 
*/
void *FSAAlloc(fsa_t *allocator);


/*****************************************************************************/
/*
Decription: Free fsa block	
Input: pointer to a block allocator.
Output:
Error proccessing: undefined behavior if the block was alreadt freed.
*/
void FSAFree(void *block);


/*****************************************************************************/
/*
Decription: returns the number of free blocks 	
Input: pointer to allocator
Output:	number of free blocks	
Error proccessing: 	-
*/
size_t FSACountFree(const fsa_t *allocator);

#endif /*__FIXED_SIZE_MEM_ALLOC_H__*/
