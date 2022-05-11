/****************************************************************************
Title: Variable Size Allocator
Author: Aviv Illoz
Description: Variable Size memory Allocator
*****************************************************************************/

#ifndef __VARIABLE_SIZE_MEM_ALLOC_H__
#define __VARIABLE_SIZE_MEM_ALLOC_H__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;
typedef struct vsa_block_header vsa_block_header_t;

/*****************************************************************************/
/*
Decription: Initialization of VSA
Input: pointer to buffer and size of buffer
Output:	pointer to VSA
Error proccessing: -
*/

vsa_t *VSAInit(void *buffer, size_t buffer_size);

/*****************************************************************************/
/*
Decription: Single VSA block allocation		
Input: pointer to VSA allocator and size of the block
Output: Pointer to allocate memory and NULL if no free space available
Error proccessing: -
*/

void *VSAAlloc(vsa_t *allocator, size_t block_size);

/*****************************************************************************/
/*
Decription: Free VSA block
Input: pointer to a block allocator
Output: -
Error proccessing: undefined behavior if the block was already free
*/

void VSAFree(void *block);

/*****************************************************************************/
/*
Decription: Provide the size of largest chunk available
Input: pointer to allocator
Output:	size of largest chunk available
Error proccessing: 	-
*/

size_t VSALargestChunkAvailable(const vsa_t *allocator);

#endif /*__VARIABLE_SIZE_MEM_ALLOC_H__*/
