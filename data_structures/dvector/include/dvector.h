/****************************************************************************
Title: Vector - Infinity Labs R&D 
Group: Ol91
Description: Dynamic vector interface
****************************************************************************/

#ifndef __DYNAMIC_VECTOR_H_ILRD_OL91__
#define __DYNAMIC_VECTOR_H_ILRD_OL91__
#include <stddef.h> 	/* size_t */

/*struct vector
{               
    	void **elements;
	size_t capacity;                    
    	size_t size;                     
};*/

typedef struct vector vector_t;

/*****************************************************************************/
/*
Decription: 		creating a new vector_t Vector; 
Input:			capasity of new Vector;
Output:			pointer to new Vector;
Error proccessing: 	in case of allocation failure - NULL will be returned;
*/
vector_t *VectorCreate(size_t initial_capacity);

/*****************************************************************************/
/*
Decription: 		freeing memory allocation of a Vector; 
Input:			vector_t pointer to a Vector;
Output:			-
Error proccessing: 	-
*/		
void VectorDestroy(vector_t *vector);	

/*****************************************************************************/
/*
Decription: 		adding a new element to the end of a Vector, reallocation can occure; 
Input:			vector_t pointer to a Vector, void pointer to a new element;
Output:			-
Error proccessing: 	returns 0 in case of success, other value in case of failure;
*/	
int VectorPushBack(vector_t *vector, void *element);

/*****************************************************************************/
/*
Decription: 		poping an element from the end of a Vector; 
Input:			vector_t pointer to a Vector;
Output:			-
Error proccessing: 	attempt to pop an element from an empty Vector;
*/
void VectorPopBack(vector_t *vector);

/*****************************************************************************/
/*
Decription: 		reallocate extra amount of space if needed; 
Input:			vector_t pointer to a Vector;
Output:			-
Error proccessing: 	in case of reallocation succes returns 0, in case of failure returns other value;
*/
int VectorReserve(vector_t *vector, size_t capacity);	

/*****************************************************************************/
/*
Decription: 		checking an amount of elements in Vector; 
Input:			vector_t pointer to a Vector;
Output:			return number of elements inside Vector;
Error proccessing: 	-
*/
size_t VectorSize(const vector_t *vector);	 

/*****************************************************************************/
/*
Decription: 		checking current capacity of Vector; 
Input:			vector_t pointer to a Vector;
Output:			current capacity;
Error proccessing: 	-
*/
size_t VectorCapacity(const vector_t *vector); 

/*****************************************************************************/
/*
Decription: 		setting an specific element in a Vector; 
Input:			vector_t pointer to a Vector, index of element, void pointer to value;
Output:			-
Error proccessing: 	-
*/
void VectorSetElement(vector_t *vector, size_t index, void *element);

/*****************************************************************************/
/*
Decription: 		getting specific element from Vector; 
Input:			vector_t pointer to a Vector, index of element;
Output:			pointer to element;
Error proccessing: 	-
*/
void *VectorGetElement(const vector_t *vector, size_t index);

/*
Decription: 		reallocate memory exactly to the current size; 
Input:			vector_t pointer to a Vector;
Output:			-
Error proccessing: 	returns 0 in case of succes, returns other value in case of reallocation failure;
*/
int VectorShrinkToFit(vector_t *vector);	


#endif
