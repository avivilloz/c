/****************************************************************************
Title: Circular Buffer
Author: Aviv Illoz
Description: Library of functions to implement a Circular Buffer.
****************************************************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, free*/
#include <stddef.h> 	/* size_t, offsetof */
#include <sys/types.h> 	/* ssize_t */
#include <assert.h>	/* assert */
#include "cbuffer.h"	/* api */

struct cbuffer
{
	size_t size;
	size_t read_index;
	size_t capacity;
	char buffer[1];
};

/****************************************************************************/

cbuffer_t *CBCreate(size_t capacity)
{
	cbuffer_t *new_buffer = (cbuffer_t *)malloc(offsetof(cbuffer_t, buffer) 
								+ (capacity));
	if (NULL == new_buffer)
	{
		return NULL;
	}

	new_buffer->size = 0;
	new_buffer->read_index = 0;
	new_buffer->capacity = capacity;
	
	return new_buffer;
}

/****************************************************************************/

void CBDestroy(cbuffer_t *c_buffer)
{
	assert(NULL != c_buffer);	
	
	free(c_buffer);
	c_buffer = NULL;
}

/****************************************************************************/

ssize_t CBWrite(cbuffer_t *c_buffer, const void *src, size_t count)
{
	size_t bytes = 0, write_index = 0, free_space = CBFreeSpace(c_buffer);

	assert(NULL != c_buffer && NULL != src);

	for (; bytes < count && free_space > 0; ++bytes, --free_space)
	{
		write_index = (c_buffer->size + c_buffer->read_index) 
							% c_buffer->capacity;
		c_buffer->buffer[write_index] = *(((char *)src) + bytes);
		++c_buffer->size;
	}

	return bytes;
}

/****************************************************************************/

ssize_t CBRead(cbuffer_t *c_buffer, void *dest, size_t count)
{
	size_t bytes = 0;

	assert(NULL != c_buffer && NULL != dest);

	for (; bytes < count && 0 != c_buffer->size; ++bytes)
	{
		*(((char *)dest) + bytes) = c_buffer->buffer[c_buffer->read_index];
		--c_buffer->size;
		c_buffer->read_index = (c_buffer->read_index + 1) 
							% c_buffer->capacity;
	}

	return bytes;
}

/****************************************************************************/

int CBIsEmpty(const cbuffer_t *c_buffer)
{
	assert(NULL != c_buffer);	

	return (0 == CBSize(c_buffer));
}	
	
/****************************************************************************/

size_t CBSize(const cbuffer_t *c_buffer)
{
	assert(NULL != c_buffer);

	return c_buffer->size;
}

/****************************************************************************/

size_t CBFreeSpace(const cbuffer_t *c_buffer)
{
	assert(NULL != c_buffer);

	return c_buffer->capacity - c_buffer->size;
}

/****************************************************************************/
