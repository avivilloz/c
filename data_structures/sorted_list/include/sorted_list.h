/****************************************************************************
Title: Sorted List
Author: Aviv Illoz
Description: Sorted list interface
****************************************************************************/

#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stddef.h>     /* typedef & size_t */
#include "dlist.h"	/* api */

/*
struct sorted_list
{
	dlist_t *list;
	int (*cmp)(const void *lhs, const void *rhs);
};
*/

typedef struct sorted_list sorted_list_t;
typedef struct sorted_list_iter sorted_list_iter_t;

struct sorted_list_iter
{
	#ifndef NDEBUG
	sorted_list_t *sorted_list;
	#endif

	dlist_iter_t iterator;
};

/*****************************************************************************/
/*
Decription:		Create new sorted list with sort rule.	
Input:			Pointer to function that rules how the list is sorted.
			Function returns int positive or 0 if element should be
			inserted, negative if not.
Output:			Pointer to a sorted list, NULL if memory allocation failed		
Error proccessing:	Memory failed to allocate
Time complexity:	O(1)
*/

sorted_list_t *SortedListCreate(int (*cmp)(const void *lhs, const void *rhs));

/*****************************************************************************/
/*
Decription:		Destroy sorted list		
Input:			Pointer to a sorted list
Output:			-		
Error proccessing:	-
Time complexity:	O(1)
*/

void SortedListDestroy(sorted_list_t *sorted_list);

/*****************************************************************************/
/*
Decription:		Inserts element to the list when return value of
			comparison function is 0 or positive, or when the tail
			of the list is reached
Input:			Pointer to a sorted list and data to insert
Output:			Iterator of the new node, if memory allocation failed
			iterator to the end of the sorted list	
Error proccessing:	Memory failed to allocate
Time complexity:	O(n)
*/

sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data);

/*****************************************************************************/
/*
Decription:		Remove element of specific iterator
Input:			Iterator to the element to remove 
Output:			Iterator to the next element		
Error proccessing:	-
Time complexity:	O(1)
*/

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter);

/*****************************************************************************/
/*
Decription:         	Returns the beginning of a sorted list
Input:              	A pointer to a sorted list
Output:             	Iterator to the beginning of a sorted list
Error proccessing: 	-
Time complexity:	O(1)
*/

sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list);

/*****************************************************************************/
/*
Decription:        	Returns the end of a sorted list
Input:              	Pointer to a sorted list
Output:             	Iterator to the end of a sorted list
Error proccessing: 	-
Time complexity:	O(1)
*/
sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list);

/*****************************************************************************/
/*
Decription:		Returns iterator to the next element	
Input:			Iterator of a sorted list
Output:			The next iterator to the iterator specified
Error proccessing: 	-
Time complexity:	O(1)
*/
sorted_list_iter_t SortedListNext(sorted_list_iter_t iter);

/*****************************************************************************/
/*
Decription:		Returns iterator to the previous element 
Input:			Iterator of a sorted list
Output:			Iterator to the previous element
Error proccessing:	-
Time complexity:	O(1)
*/
sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter);

/*****************************************************************************/
/*
Decription:		Compares two iterators of a sorted list
Input:			Two iterators of a sorted list
Output:             	1 if iterators are the same, 0 if different
Error proccessing:	-
Time complexity:	O(1)
*/            
int SortedListIsSameIterator(sorted_list_iter_t lhs, sorted_list_iter_t rhs);

/*****************************************************************************/
/*
Decription:		Gets data from iterator of a sorted list	
Input:			Iterator of a sorted list
Output:			Data contained in the node of iterator specified
Error proccessing:	Get data from SortedListEnd - core dump
Time complexity:	O(1)
*/
void *SortedListGetData(sorted_list_iter_t iter);

/*****************************************************************************/
/*
Decription:		Pop elements at the beginning of the sorted list	
Input:			Pointer to a sorted list
Output:			Pointer to the data of popped element		
Error proccessing:  	Pop from an empty list - undefined behaviour
Time complexity:	O(1)
*/

void *SortedListPopFront(sorted_list_t *sorted_list);

/*****************************************************************************/
/*
Decription:		Pop elements at the end of the sorted list	
Input:			Pointer to a sorted list
Output:			Pointer to the data of popped element		
Error proccessing:	Pop from an empty list - undefined behaviour
Time complexity:	O(1)
*/

void *SortedListPopBack(sorted_list_t *sorted_list);

/*****************************************************************************/
/*
Decription:         	Checks if the sorted list is empty	
Input:              	A sorted list
Output:             	1 if sorted list is empty, 0 if not
Error proccessing:  	-
Time complexity:	O(1)
*/

int SortedListIsEmpty(const sorted_list_t *sorted_list);

/*****************************************************************************/
/*
Decription:         	Returns size of the sorted list 
Input:              	A pointer to sorted list
Output:             	Size of the sorted linked list
Error proccessing:  	-
Time complexity:	O(n)
*/

size_t SortedListSize(const sorted_list_t *sorted_list);

/*****************************************************************************/
/*
Decription:         	Applies user defined function to the spcific range of a
			sorted list	
Input:              	Range from iterator "from" to iterator "to", function
			action and parameter
Output:            	0 if succesfull, 1 if not (the same as action function)
Error proccessing:  	User's function fail
Time complexity:	O(n)
*/

int SortedListForEach(
	sorted_list_iter_t from,
	sorted_list_iter_t to,
	int (*action)(void *data, void *param), 
	void *param
);

/*****************************************************************************/
/*
Decription:        	Traverse a specific range of a sorted list to find
			specified element according to the sorting condition	
Input:              	Range from iterator "from" to iterator "to", comparator
			function, element to find
Output:             	First found iterator to requested element or "to" if no
			match is found
Error proccessing: 	-
Time complexity:	O(n)
*/

sorted_list_iter_t SortedListFind(
	sorted_list_t *sorted_list,
	sorted_list_iter_t from,
	sorted_list_iter_t to,
	const void *element_to_find
);

/*****************************************************************************/
/*
Decription:        	Traverse a specific range of a sorted list to find
			specified element if not alligned to sorting condition	
Input:              	Range from iterator "from" to iterator "to", comparator
			function, element to find
Output:             	First found iterator to requested element or "to" if no
			match is found
Error proccessing: 	-
Time complexity:	O(n)
*/

sorted_list_iter_t SortedListFindIf(
	sorted_list_iter_t from,
	sorted_list_iter_t to,
	int (*is_match)(const void *data, const void *element_to_find),
	const void *element_to_find
);

/*****************************************************************************/
/*
Decription:        	Merges sorted list src into sorted list dest	
Input:              	Two pointers to sorted lists
Output:             	-
Error proccessing: 	Both sorted lists must have the same comparison function
Time complexity:	O(n)
*/

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src);

#endif /* __SORTED_LIST_H__ */
