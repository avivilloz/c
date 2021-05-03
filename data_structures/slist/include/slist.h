/****************************************************************************
Title: Slist - Infinity Labs R&D 
Group: Ol91
Description: Dynamic Linked List interface
****************************************************************************/

#include <stddef.h>	/*size_t*/

#ifndef __DYNAMIC_Llist_H_ILRD_OL91__
#define __DYNAMIC_Llist_H_ILRD_OL91__
 
typedef struct slist slist_t; 
typedef struct slist_node slist_node_t;
typedef slist_node_t* slist_iter_t;

/*****************************************************************************/
/*
Decription: Create new linked list		
Input:			
Output:	Iterator to a new linked list		
Error proccessing: 	memory failed to allocate
*/
slist_t *SListCreate(void);
/*****************************************************************************/
/*
Decription: 	Deletes linkedd list and frees all allocations	
Input:			Iterator to linked list
Output:			
Error proccessing: 	
*/
void SListDestroy(slist_t *slist);
/*****************************************************************************/
/*
Decription: 	Returns the beginning of linked list
Input:			A linked list
Output:			Iterator to the beginning of the linked list
Error proccessing: 	
*/

slist_iter_t SListBegin(const slist_t *slist);
/*****************************************************************************/
/*
Decription: 	Returns the end of the linked list
Input:			A linked list
Output:			Iterator to the end of the linked list
Error proccessing: 	
*/
slist_iter_t SListEnd(const slist_t *slist);
/*****************************************************************************/
/*
Decription: 	Next element	
Input:			An iterator to the linked list
Output:			An iterator to the next element of the linked list
Error proccessing: 	Next eslist_t *slistlement is non existent
*/
slist_iter_t SListNext(slist_iter_t iter); 
/*****************************************************************************/
/*
Decription: 	Compares two iterators	
Input:			Two iterators to the linked list
Output:			0 if iterators are the same, 1 if different
Error proccessing: 	Invalid iterator
*/            
int SListIsSameIterator(const slist_iter_t lhs,const slist_iter_t rhs);
/*****************************************************************************/
/*
Decription: 	Gets data from node of linked list	
Input:			Iterator to the linked list
Output:			Data located on the node that iterator points to
Error proccessing: 	Invalid iterator
*/
void *SListGetData(const slist_iter_t iter);
/*****************************************************************************/
/*
Decription: 	Assigns data to a node 	
Input:			Iterator to the linked list
Output:			
Error proccessing: 	Invalid iterator
*/
void SListSetData(slist_iter_t iter, void *data);
/*****************************************************************************/
/*
Decription: 	Inserts a node into the linked list	
Input:			Iterator to the place of insert, data for insertion
Output:			Iterator to the new node
Error proccessing: 	Invalid iterator
*/

slist_iter_t SListInsert(slist_iter_t iter, void *data);
/*****************************************************************************/
/*
Decription: 	Removes a node from the linked list	
Input:			Iterator to the node that needs to be deleted
Output:			
Error proccessing: 	Invalid iterator
*/
slist_iter_t SListRemove(slist_iter_t iter);
/*****************************************************************************/
/*
Decription: 	Returns size of the linked list 
Input:			A linked list
Output:			Size of the linked list
Error proccessing: 	Non existent linked list
*/
size_t SListSize(const slist_t *slist);
/*****************************************************************************/
/*
Decription: 	Checks if linked list is empty	
Input:			A linked list
Output:			0 if linked list is empty, other value if not
Error proccessing: 	Nonexistent linked list
*/
int SListIsEmpty(const slist_t *iter);
/*****************************************************************************/
/*
Decription: 	Searches linked list in specific range for requested element	
Input:			Iterators for range, comparator function, element to find
Output:			Iterator to requested element
Error proccessing: 	Element not found or found more than one
*/
slist_iter_t SListFind(
    const slist_iter_t from,
    const slist_iter_t to,
    int (*is_match)(const void *data, const void *element_to_find),
    const void *element_to_find
);
/*
Decription: 	Applies user defined function to a range of elements	
Input:			Iterators for range, action function
Output:			0 if succesfull else 1 if not (the same as action function)
Error proccessing: 	
*/
int SListForEach(
    const slist_iter_t from,
    const slist_iter_t to,
    int (*action)(void *data, void *param),
    void *param
);

/********************************* MY FUNCS ************************************/

void SListAppend(slist_t *dest, slist_t *src);

#endif



