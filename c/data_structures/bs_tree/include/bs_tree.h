/****************************************************************************
Title: Binary Sorted Tree
Author: Aviv Illoz
Description: Binary Sorted Tree API
*****************************************************************************/

#ifndef __BS_TREE__
#define __BS_TREE__

#include <stddef.h>	/* size_t */

typedef struct bst bst_t;
typedef struct bst_node bst_node_t;
typedef struct bst_iter
{
	bst_node_t *node;
} bst_iter_t;

/*****************************************************************************/
/*
Decription: Creates tree
Input: Compare Funtion to determine if node will be placed on the right or left
Output: "bst struct" with the stub and function
Error: NULL if failed to allocate
Time complexity: O(1)
*/

bst_t *BSTCreate(int (*is_before)(const void *lhs, const void *rhs));

/*****************************************************************************/
/*
Decription: Destroyes tree
Input: "bst struct"
Output: -
Error: -
Time complexity: O(n)
*/

void BSTDestroy(bst_t *tree);

/*****************************************************************************/
/*
Decription: Size of tree
Input: "bst struct"
Output: Number of nodes in tree
Error: - 
Time complexity: O(n)
*/

size_t BSTSize(const bst_t *tree);

/*****************************************************************************/
/*
Decription: Determines if tree is empty of nodes or not	
Input: "bst struct"
Output: boolian value: 1 if empty, 0 if not empty
Error: -
Time complexity: O(1)
*/

int BSTIsEmpty(const bst_t *tree);

/*****************************************************************************/
/*
Decription: Inserts node in tree	
Input: "bst struct" and data
Output: Iterator to inserted node
Error: Returns empty iterator if failed to allocate
Time complexity: worst - O(n)
		 average - O(log n)
*/

bst_iter_t BSTInsert(bst_t *tree, void *data);

/*****************************************************************************/
/*
Decription: Removes node from tree
Input: Iterator
Output: -
Error: -
Time complexity: O(1)
*/

void BSTRemove(bst_iter_t iter);

/*****************************************************************************/
/*
Decription: Beginning of tree
Input: "bst struct"
Output: Iterator to the node that contains the smallest value of Tree
Error: - 
Time complexity: O(log n)
*/

bst_iter_t BSTBegin(const bst_t *tree);

/*****************************************************************************/
/*
Decription: End of tree	
Input: "bst struct"
Output: Iterator to stub
Error: -
Time complexity: O(1)
*/

bst_iter_t BSTEnd(const bst_t *tree);

/*****************************************************************************/
/*
Decription: Previous node
Input: "bst_iter struct"
Output: Iterator to left child (i.e smaller), or parent of "bst_iter struct" if 
	it is the right child of its parent (i.e if is bigger than its parent)
Error: Returns empty iterator if it is the left child of its parent and has no 
	left child to itself
Time complexity: O(1)
*/

bst_iter_t BSTPrev(bst_iter_t iter);

/*****************************************************************************/
/*
Decription: Next node
Input: "bst_iter struct"
Output: Iterator to right child (i.e bigger), or parent of "bst_iter struct" if 
	it is the left child of its parent (i.e if is smaller than its parent)
Error: Returns empty iterator if it is the right child of its parent and has no 
	right child to itself
Time complexity: O(1)
*/

bst_iter_t BSTNext(bst_iter_t iter);

/*****************************************************************************/
/*
Decription: Checks if 2 iterators are equal
Input: 2 "bst_iter structs"
Output: boolian value: 1 if they are equal, 0 if they are not equal
Error: -
Time complexity: O(1)
*/

int BSTIterIsEqual(bst_iter_t lhs, bst_iter_t rhs);

/*****************************************************************************/
/*
Decription: Gets data from node	
Input: "bst_iter struct"
Output: Data from node
Error: -
Time complexity: O(1)
*/

void *BSTGetData(bst_iter_t iter);

/*****************************************************************************/
/*
Decription: Finds node with specific data
Input: "bst struct" and data to find
Output: Iterator to node with data specified
Error: Returns empty iterator if not found
Time complexity: O(n)
*/

bst_iter_t BSTFind(bst_t *tree, void *data);

/*****************************************************************************/
/*
Decription: Performs a certain action for each node included in the range
Input: Iterator from and to (to determine the range), function with action to 
	perform, and parameter for the action function
Output: boolian value: 1 if failed, 0 if succeeded
Error: - 
Time complexity: O(3n)
*/

int BSTForEach(
	bst_iter_t from,
	bst_iter_t to,
	int (*action)(void *data, void *params),
	void *params
	);

/*****************************************************************************/

#endif /*__BS_TREE__*/
