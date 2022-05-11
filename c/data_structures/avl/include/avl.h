/****************************************************************************
Title: Binary Sorted Tree (Recursive)
Author: Aviv Illoz
Description: Binary Sorted Tree (Recursive) API
*****************************************************************************/

#ifndef __BS_TREE_RECURSIVE__
#define __BS_TREE_RECURSIVE__

#include <stddef.h>  /* size_t */ 

typedef struct avl_node avl_node_t;
typedef struct avl avl_t;

/*****************************************************************************/
/*
Decription: Creates tree
Input: Compare Funtion to determine if node will be placed on the right or left
Output: pointer to avl_t struct
Error: NULL if failed to allocate
Time complexity: O(1)
*/

avl_t *AVLCreate(int (*is_before)(const void *lhs, const void *rhs));

/*****************************************************************************/
/*
Decription: Destroyes tree
Input: "avl struct"
Output: -
Error: -
Time complexity: O(n)
*/

void AVLDestroy(avl_t *tree);

/*****************************************************************************/
/*
Decription: Size of tree
Input: "avl struct"
Output: Number of nodes in tree
Error: - 
Time complexity: O(n)
*/

size_t AVLSize(const avl_t *tree);

/*****************************************************************************/
/*
Decription: Determines if tree is empty of nodes or not	
Input: "avl struct"
Output: boolian value: 1 if empty, 0 if not empty
Error: -
Time complexity: O(1)
*/


int AVLIsEmpty(const avl_t *tree);

/*****************************************************************************/
/*
Decription: Inserts node in tree	
Input: "avl struct" and data
Output: Pointer to inserted node
Error: Returns 1 if failed, 0 if success
Time complexity: worst - O(n)
		 average - O(log n)
*/

int AVLInsert(avl_t *tree, void *data);

/*****************************************************************************/
/*
Decription: Removes node from tree
Input: avl struct and data
Output: -
Error: -
Time complexity: O(log n)
*/

void AVLRemove(avl_t *tree, const void *data);

/*****************************************************************************/
/*
Decription: Height of tree
Input: "avl struct"
Output: Number of "levels"
Error: - 
Time complexity: O(log n)
*/

size_t AVLHeight(const avl_t *tree);

/*****************************************************************************/

/*
Decription: Finds node with specific data
Input: "avl struct" and data to find
Output: Pointer to data
Error: Returns NULL pointer if not found
Time complexity: O(n)
*/

void *AVLFind(const avl_t *tree, void *data);

/*****************************************************************************/
/*
Decription: Performs a certain action for each node in the tree structure
Input: Pointer to tree, function with action to perform, and parameter for the 
action function
Output: boolian value: 1 if failed, 0 if succeeded
Error: - 
Time complexity: O(3n)
*/

int AVLForEach(
	avl_t *tree,
	int (*action)(void *data, void *params),
	void *params
);

/*****************************************************************************/

#endif /*__BS_TREE_RECURSIVE__*/
