/****************************************************************************
Title: Doubly Linked List
Author: Aviv Illoz
Description: Doubly Linked list interface
****************************************************************************/

#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <stddef.h>     /* typedef */

typedef struct dlist_node dlist_node_t;
typedef struct dlist dlist_t;
typedef struct dlist_iterator dlist_iter_t;

struct dlist_iterator
{
    	dlist_node_t *dlist_node;
};


/*
***** source file ******

struct dlist_node
{
        void *data;
        struct dlist_node *next;
        struct dlist_node *prev;
};

struct dlist
{
	dlist_node_t *head;
	dlist_node_t *tail;
};

struct dlist_iterator
{
    dlist_node_t *dlist_node;
};
*/

/*****************************************************************************/
/*
Decription:         Create new double linked list		
Input:              No
Output:             Iterator to a new double linked list		
Error proccessing:  memory failed to allocate
*/
dlist_t *DListCreate(void);

/*****************************************************************************/
/*
Decription:         Delete double linked list and free all allocations	
Input:              Iterator to double linked list
Output:             No
Error proccessing: 	
*/
void DListDestroy(dlist_t *list);

/*****************************************************************************/
/*
Decription:         Returns the beginning of double linked list
Input:              A pointer to double linked list
Output:             Iterator to the beginning of the double linked list
Error proccessing: 	
*/

dlist_iter_t DListBegin(const dlist_t *list);

/*****************************************************************************/
/*
Decription:         Returns the end of the double linked list
Input:              A double linked list
Output:             Iterator to the end of the double linked list
Error proccessing: 	
*/
dlist_iter_t DListEnd(const dlist_t *list);

/*****************************************************************************/
/*
Decription:         Return iterator to next element	
Input:              An iterator to the double linked list
Output:             An iterator to the next element of the double linked list
Error proccessing: 	No
*/
dlist_iter_t DListNext(dlist_iter_t iterator);

/*****************************************************************************/
/*
Decription:         Return iterator to previous element 
Input:              An iterator to the double linked list
Output:             An iterator to the previous element of the double linked list
Error proccessing:  No
*/
dlist_iter_t DListPrev(dlist_iter_t iterator);

/*****************************************************************************/
/*
Decription:         Compares two iterators	
Input:              Two iterators to the double linked list
Output:             1 if iterators are the same, 0 if different
Error proccessing:  No
*/            
int DListIsSameIterator(dlist_iter_t lhs, dlist_iter_t rhs);

/*****************************************************************************/
/*
Decription:         Gets data from node of double linked list	
Input:              Iterator to the double linked list
Output:             Data located on the node that iterator points to
Error proccessing:  No
*/
void *DListGetData(dlist_iter_t iterator);

/*****************************************************************************/
/*
Decription:      	Assigns data to a node
Input:  			Iterator to the double linked list
Output:             No
Error proccessing:  No
*/
void DListSetData(dlist_iter_t iterator, void *data);

/*****************************************************************************/
/*
Decription:         Inserts a node into the double linked list	
Input:              Iterator before which need to insert, data for insertion
Output:             Iterator to the new node
Error proccessing: 	Allocation fail
*/

dlist_iter_t DListInsert(dlist_iter_t iterator, void *data);

/*****************************************************************************/
/*
Decription:         Removes a node from the double linked list	
Input:              Iterator to the node that needs to be deleted
Output:             Iterator to next node
Error proccessing: 	No
*/
dlist_iter_t DListRemove(dlist_iter_t iterator);

/*****************************************************************************/
/*
Decription:         Returns size of the double linked list 
Input:              A pointer to double linked list
Output:             Size of the double linked list
Error proccessing: 	No
*/
size_t DListSize(const dlist_t *list);

/*****************************************************************************/
/*
Decription:         Checks if double linked list is empty	
Input:              A double linked list
Output:             1 if double linked list is empty, 0 if not
Error proccessing: 	No
*/
int DListIsEmpty(const dlist_t *list);

/*****************************************************************************/
/*
Decription:         Searches linked list in specific range for requested element    
Input:              Iterators for range, comparator function, element to find
Output:             First founded iterator to requested element. If there's no
                    match, return iterator "to".
Error proccessing: 	No
*/
dlist_iter_t DListFind(
    dlist_iter_t from,
    dlist_iter_t to,
    int (*is_match)(const void *data, const void *element_to_find),
    const void *element_to_find
);

/*****************************************************************************/
/*
Decription:         Applies user defined function to a range of elements	
Input:              Iterators for range, action function
Output:             0 if succesfull, 1 if not (the same as action function)
Error proccessing:  User's function fail
*/
int DListForEach(
    dlist_iter_t from,
    dlist_iter_t to,
    int (*action)(void *data, void *param),
    void *param
    );

/*****************************************************************************/
/*
Decription:         Finds all matched nodes and copy them to output_list
Input:              iterators for range, match function, output_list
Output:             0 if successfull, -1 if allocation fail, 1 if no matches
Error proccessing:  Allocation fail
*/
int DListMultiFind(
    dlist_iter_t from,
    dlist_iter_t to,
    int(*is_match)(const void *data, const void *param),
    const void *param,
    dlist_t *output_list
    );

/*****************************************************************************/
/*
Decription:         Add new node in the beginning of the list
Input:              A list, data
Output:             New iterator, iterator to the end of list in case of fail
Error proccessing:  Allocation fail
*/
dlist_iter_t DListPushFront(dlist_t *dlist, void *data);

/*****************************************************************************/
/*
Decription:         Add new node in the end of the list
Input:              A list, data
Output:             New iterator, iterator to the end of list in case of fail
Error proccessing:  Allocation fail
*/
dlist_iter_t DListPushBack(dlist_t *dlist, void *data);

/*****************************************************************************/
/*
Decription:         Delete a node in the beginning of the list
Input:              A list
Output:             Data
Error proccessing:  No
*/
void *DListPopFront(dlist_t *dlist);

/*****************************************************************************/
/*
Decription:         Delete a node in the end of the list
Input:              A list
Output:             Data
Error proccessing:  No
*/
void *DListPopBack(dlist_t *dlist);

/*****************************************************************************/
/*
Decription:         Put nodes in range of "from" "to" after the node "where"
                    Src list is redused, and nodes before "from" and after "to"
                    are connected (if possible)
Input:              Iterator from, to and where
Output:             Iterator to where
Error proccessing:  No
*/
dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where);

/*****************************************************************************/

#endif /* __DOUBLY_LINKED_LIST_H__ */
