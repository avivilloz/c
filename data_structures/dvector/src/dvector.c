/****************************************************************************
Title: Vector - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Igor
Description: Dynamic vector interface
****************************************************************************/

#include <stdlib.h>	/* malloc */
#include <stddef.h>	/* size_t */
#include <assert.h>	/* assert */
#include "dvector.h"	/* api */

struct vector
{
	void **elements;
	size_t capacity;
	size_t size;
};

/****************************************************************************/

vector_t *VectorCreate(size_t initial_capacity)
{
	size_t vector_size = sizeof(vector_t);
	vector_t *return_vector = malloc(vector_size);
	if (NULL == return_vector)
	{
		return NULL;
	}
	
	return_vector->elements = malloc(initial_capacity * sizeof(size_t));
	if (NULL == return_vector->elements)
	{
		free(return_vector);
		return_vector = NULL;
		return NULL;
	}

	return_vector->capacity = initial_capacity;
	return_vector->size = 0;

	return return_vector;
}

/****************************************************************************/

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);

	free(vector->elements);
	vector->elements = NULL;

	free(vector);
	vector = NULL;
}

/****************************************************************************/

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);

	return vector->size;
}

/****************************************************************************/

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);

	return vector->capacity;
}

/****************************************************************************/

int VectorPushBack(vector_t *vector, void *element)
{
	int check = 0;

	assert(NULL != vector);

	if (vector->capacity == vector->size)
	{
		check = VectorReserve(vector, (vector->capacity * 2));
		if (check)
		{
			return 1;
		}
	}

	vector->elements[vector->size] = element;
	vector->size += 1;

	return 0;
}

/****************************************************************************/

void VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);

	vector->size -= 1;
}

/****************************************************************************/

void *VectorGetElement(const vector_t *vector, size_t index)
{
	assert(NULL != vector);

	if (index >= vector->size)
	{
		return NULL;
	}

	return vector->elements[index];
}

/****************************************************************************/

void VectorSetElement(vector_t *vector, size_t index, void *element)
{
	assert(NULL != vector);

	if (index >= vector->capacity)
	{
		return;
	}

	vector->elements[index] = element;
}

/****************************************************************************/

int VectorReserve(vector_t *vector, size_t capacity)
{
	void **temp = NULL;
	
	assert(NULL != vector);

	if (capacity <= vector->size)
	{
		return 1;
	}

	vector->capacity = capacity;
	temp = realloc(vector->elements, vector->capacity * sizeof(size_t));

	if (NULL == temp)
	{
		return 1;
	}

	vector->elements = temp;
	temp = NULL;

	return 0;
}

/****************************************************************************/

int VectorShrinkToFit(vector_t *vector)
{
	void **temp = NULL;

	assert(NULL != vector);

	vector->capacity = vector->size;
	temp = realloc(vector->elements, vector->capacity * sizeof(size_t));
	if (NULL == temp)
	{
		return 1;
	}

	vector->elements = temp;
	temp = NULL;

	return 0;
}


