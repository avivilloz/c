/****************************************************************************
Title: Binary Sorted Tree - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Nathan
Description: Binary Sorted Tree API
*****************************************************************************/

#include <stdlib.h>	/* malloc */
#include <assert.h>	/* assert */
#include "bs_tree.h"	/* api */

/*****************************************************************************/

enum {
	LEFT,
	RIGHT,
	NUM_OF_CHILDREN
};

struct bst_node
{
	void *data;
	bst_node_t *parent;
	bst_node_t *children[NUM_OF_CHILDREN];
};

struct bst
{
	int (*is_before)(const void *lhs, const void *rhs);
	bst_node_t stub;
};

/*****************************************************************************/

enum {SUCCESS, FAILURE};

/*************************** GENERAL STATIC FUNCS ****************************/

static bst_iter_t GetLeftChild(bst_iter_t iter)
{
	iter.node = iter.node->children[LEFT];

	return iter;
}

static bst_iter_t GetRightChild(bst_iter_t iter)
{
	iter.node = iter.node->children[RIGHT];

	return iter;
}

static bst_iter_t GetParent(bst_iter_t iter)
{
	iter.node = iter.node->parent;

	return iter;
}

static bst_node_t *IterToNode(bst_iter_t iter)
{	
	return iter.node;
}

static bst_iter_t NodeToIter(bst_node_t *node)
{	
	bst_iter_t iter;
	iter.node = node;

	return iter;
}

static int IterIsNull(bst_iter_t iter)
{
	return (NULL == IterToNode(iter));
}

/*static int IsBefore(const void *lhs, const void *rhs)
{
	return (*(int *)lhs > *(int *)rhs);
}*/

/*********************** NEXT AND PREV STATIC FUNCS **************************/

static int IsRightChild(bst_iter_t iter)
{
	bst_node_t *child = IterToNode(iter);
	bst_node_t *parent = child->parent;
	
	return (parent->children[RIGHT] == child);
}

static int IsBeforeStub(bst_iter_t iter)
{
	return (NULL == IterToNode(GetParent(GetParent(iter))));
}

/************************** REMOVE STATIC FUNCS ******************************/

static int GetChildSide(bst_node_t *parent, bst_node_t *node)
{
	if (parent->children[LEFT] == node)
	{
		return LEFT;
	}	
	else
	{
		return RIGHT;
	}
}

/************************** DESTROY STATIC FUNCS *****************************/

static int IsLeaf(bst_iter_t iter)
{
	bst_node_t *node = IterToNode(iter);

	return (NULL == node->children[LEFT] && NULL == node->children[RIGHT]);
}

static int HasLeftChild(bst_node_t *node)
{
	return (NULL != node->children[LEFT]);
}

static bst_iter_t GoToLeaf(bst_iter_t iter)
{
	bst_node_t *node = IterToNode(iter);

	for (; !IsLeaf(NodeToIter(node))
		; node = node->children[!HasLeftChild(node)])
	{}

	return NodeToIter(node);
}

/***************************** MAIN FUNCS ***********************************/

bst_t *BSTCreate(int (*is_before)(const void *lhs, const void *rhs))
{
	bst_t *new_tree = NULL;

	assert(NULL != is_before);

	new_tree = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == new_tree)
	{
		return NULL;
	}

	new_tree->is_before = is_before;
	new_tree->stub.parent = NULL;
	new_tree->stub.children[LEFT] = NULL;
	new_tree->stub.children[RIGHT] = NULL;

	return new_tree;
}

/*****************************************************************************/

void BSTDestroy(bst_t *tree)
{
	bst_iter_t iter, parent;

	assert(NULL != tree);

	for (iter = BSTBegin(tree); !BSTIsEmpty(tree); iter = parent)
	{
		if (!IsLeaf(iter))
		{
			iter = GoToLeaf(iter);
		}

		parent = GetParent(iter);
		BSTRemove(iter);
	}

	free(tree);
	tree = NULL;
}

/*****************************************************************************/

size_t BSTSize(const bst_t *tree)
{
	bst_iter_t iter;
	size_t counter = 0;

	assert(NULL != tree);

	for (iter = BSTBegin(tree)
		; !BSTIterIsEqual(iter, BSTEnd(tree))
		; iter = BSTNext(iter), ++counter)
	{}

	return counter;
}

/*****************************************************************************/

int BSTIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);

	return (NULL == tree->stub.children[LEFT]);
}

/*****************************************************************************/

bst_iter_t BSTInsert(bst_t *tree, void *data)
{
	bst_node_t *new_node = NULL;
	bst_node_t *parent = &tree->stub;
	int child_side = LEFT;
	
	assert(NULL != tree);
	
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
	{
		return BSTEnd(tree);
	}

	for (; NULL != parent->children[child_side]
		; parent = parent->children[child_side]
		, child_side = !tree->is_before(parent->data, data))
	{}

	new_node->data = data;
	new_node->parent = parent;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	parent->children[child_side] = new_node;

	return NodeToIter(new_node);
}

/*****************************************************************************/

void BSTRemove(bst_iter_t iter)
{
	bst_node_t *node = IterToNode(iter);
	bst_node_t *parent = IterToNode(GetParent(iter));
	bst_node_t *left_child = IterToNode(GetLeftChild(iter));
	bst_node_t *right_child = IterToNode(GetRightChild(iter));
	int child_side = GetChildSide(parent, node);

	if (NULL != right_child)
	{
		parent->children[child_side] = right_child;
		right_child->parent = parent;		

		if (NULL != left_child)
		{
			for (; NULL != right_child->children[LEFT]
					; right_child = right_child->children[LEFT])
			{}

			right_child->children[LEFT] = left_child;
			left_child->parent = right_child;
		}
	}
	else if (NULL != left_child)
	{
		parent->children[child_side] = left_child;
		left_child->parent = parent;
	}
	else
	{
		parent->children[child_side] = NULL;
	}

	free(node);
	node = NULL;
}

/*****************************************************************************/

bst_iter_t BSTBegin(const bst_t *tree)
{
	bst_iter_t iter = GetLeftChild(BSTEnd(tree));

	assert(NULL != tree);

	if (IterIsNull(iter))
	{
		return BSTEnd(tree);
	}
	
	for (; !IterIsNull(GetLeftChild(iter)); iter = GetLeftChild(iter))
	{}
	
	return iter;
}

/*****************************************************************************/

bst_iter_t BSTEnd(const bst_t *tree)
{
	assert(NULL != tree);

	return NodeToIter(&((bst_t *)tree)->stub);
}

/*****************************************************************************/

bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_iter_t go_down = GetLeftChild(iter);

	for (; !IterIsNull(go_down)
		&& !IterIsNull(GetRightChild(go_down))
		; go_down = GetRightChild(go_down))
	{}

	if (!IterIsNull(go_down))
	{
		return go_down;
	}

	for (; !IsBeforeStub(iter) && !IsRightChild(iter)
		; iter = GetParent(iter))
	{}	

	if (!IsBeforeStub(iter))
	{
		iter = GetParent(iter);
		return iter;
	}

	return go_down;
}

/*****************************************************************************/

bst_iter_t BSTNext(bst_iter_t iter)
{
	bst_iter_t go_down = GetRightChild(iter);

	for (; !IterIsNull(go_down)
		&& !IterIsNull(GetLeftChild(go_down))
		; go_down = GetLeftChild(go_down))
	{}

	if (!IterIsNull(go_down))
	{
		return go_down;
	}

	for (; IsRightChild(iter); iter = GetParent(iter))
	{}

	iter = GetParent(iter);

	return iter;
}

/*****************************************************************************/

int BSTIterIsEqual(bst_iter_t lhs, bst_iter_t rhs)
{
	return (IterToNode(lhs) == IterToNode(rhs));
}

/*****************************************************************************/

void *BSTGetData(bst_iter_t iter)
{
	return IterToNode(iter)->data;
}

/*****************************************************************************/

bst_iter_t BSTFind(bst_t *tree, void *data)
{
	int child_side = LEFT;
	bst_node_t *node = tree->stub.children[child_side];
	
	assert(NULL != tree);

	for (; NULL != node
		; child_side = !tree->is_before(node->data, data)
		, node = node->children[child_side])
	{
		if (node->data == data)
		{
			return NodeToIter(node);
		}
	}

	return BSTEnd(tree);
}

/*****************************************************************************/

int BSTForEach(
	bst_iter_t from,
	bst_iter_t to,
	int (*action)(void *data, void *params),
	void *params
)
{
	bst_iter_t temp;

	assert(NULL != action);
	
	for (; !BSTIterIsEqual(from, to); from = temp)
	{
		temp = BSTNext(from);
		if (action(BSTGetData(from), params))
		{
			return FAILURE;
		}
	}

	return SUCCESS;
}

