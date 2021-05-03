/******************************************************************************
Title: Heap - Infinity Labs R&D 
Group: Ol91
Description: Heap interface
******************************************************************************/

#ifndef __HEAP_OL91__
#define __HEAP_OL91__

#include <stddef.h>	/* size_t */ 
#include "dvector.h"

typedef int (*is_before_t)(const void * , const void * );
typedef int (*is_match_t)(const void *data , const void *param );
typedef struct heap heap_t;

/*****************************************************************************/
/*
Decription: 	Creates a binary heap
Input:			Capacity and compare function
Output:			pointer to new binary heap
Error proccessing: 	in case of allocation failure - NULL will be returned;
Time complexity: O(1)
*/
heap_t *HeapCreate(is_before_t is_before);
/*****************************************************************************/
/*
Decription: 	Destroys a binary heap, frees all allocated memory
Input:			pointer to a Binary heap 
Output:			none
Error proccessing: none
Time complexity: 	O(1)
*/
void HeapDestroy(heap_t *heap);
/*****************************************************************************/
/*
Decription: 	Pushes a new element to a binary heap
Input:			pointer to a Binary heap and data to push
Output:			0 if insertion was a success, non-zero if it failed
Error proccessing: 
Time complexity:O(logN)	
*/
int HeapPush(heap_t *heap, void *data);
/*****************************************************************************/
/*
Decription: 	Pops root from a heap
Input:			pointer to a Binary heap 
Output:			
Error proccessing: if heap is empty undifined beaviour
Time complexity: 	O(logN)
*/
void HeapPop(heap_t *heap);
/*****************************************************************************/
/*
Decription: 	Get data from root node
Input:			pointer to a Binary heap 
Output:			
Error proccessing: 
Time complexity: O(1)
*/
void *HeapPeek(heap_t *heap);
/*****************************************************************************/
/*
Decription: 	Gets size of a binary heap
Input:			pointer to a Binary heap 
Output:			
Error proccessing: O(1)
*/
size_t HeapSize(const heap_t *heap);
/*****************************************************************************/
/*
Decription: 	Checks is given binary heap empty
Input:			pointer to a Binary heap 
Output:			
Error proccessing: 
Time complexity: O(1)
*/
int HeapIsEmpty(const heap_t *heap);
/*****************************************************************************/
/*
Decription: 	Removes specific element from binary heap
Input:			pointer to a Binary heap and data for removal
Output:			Match data for param if succesfull, NULL if failure
Error proccessing:
Time complexity:  O(N)
*/
void *HeapRemove(heap_t *heap, is_match_t is_match, void *param);

#endif /* __HEAP_OL91__ */
