/****************************************************************************
Title: Binary Sorted Tree (Recursive) 
Author: Aviv
Description: Binary Sorted Tree (Recursive) API
*****************************************************************************/

#include <stdlib.h>	/* malloc */
#include <assert.h>	/* assert */
#include "avl.h"	/* api */

enum 
{
	RIGHT,
	LEFT,
	NUM_OF_CHILDREN
};	

struct avl_node
{
	void *data;
	size_t height;
	avl_node_t *children[NUM_OF_CHILDREN];
};

struct avl
{
	int (*is_before)(const void *lhs, const void *rhs);
	avl_node_t *root;
};

enum {SUCCESS, FAILURE};

static void DestroyNodes(avl_node_t *iter);
static void Remove(avl_node_t *node);
static size_t Count(avl_node_t *iter);
static avl_node_t *CreateNode(
	void *data, 
	size_t height,
	avl_node_t *left_child, 
	avl_node_t *right_child
);
static void InitNode(
	avl_node_t *node,
	void *data, 
	size_t height,
	avl_node_t *left_child, 
	avl_node_t *right_child
);
static avl_node_t *FindAndInsert(
	avl_t *tree,
	avl_node_t *iter,
	avl_node_t *new_node, 
	void *data
);
static int IsBalanced(avl_node_t *node);
static int CheckBalance(avl_node_t *lhs, avl_node_t *rhs);
static avl_node_t *Balance(avl_node_t *node);
static int GetCase(avl_node_t *node);
static size_t UpdateHeight(avl_node_t *node);
static size_t GetBiggestHeight(avl_node_t *node);
static avl_node_t *FindAndRemove(avl_t *tree, avl_node_t *iter, const void *data);
static int IsMatch(
	const void *lhs, 
	const void *rhs, 
	int (*is_before)(const void *lhs, const void *rhs)
);
static avl_node_t *UpdateChildrenAndRemove(avl_node_t *iter);
static void *Find(
	int (*is_before)(const void *lhs, const void *rhs),
	avl_node_t *iter,
	void *data
);
static int PerformAction(
	avl_node_t *iter, 
	int (*action)(void *data, void *params),
	void *params
);

static void SetRoot(avl_t *tree, avl_node_t *root)
{
	tree->root = root;
}

static void SetData(avl_node_t *node, void *data)
{
	node->data = data;
}

static void SetHeight(avl_node_t *node, size_t height)
{
	node->height = height;
}

static void SetChild(avl_node_t *parent, avl_node_t *child, int child_side)
{
	parent->children[child_side] = child;
}

static void *GetData(avl_node_t *node)
{
	return node->data;
}

static size_t GetHeight(avl_node_t *node)
{
	return node->height;
}

static avl_node_t *GetChild(avl_node_t *parent, int child_side)
{
	return parent->children[child_side];
}

static int HasChild(avl_node_t *node, int child_side)
{
	return (NULL != node->children[child_side]);
}

static int HasBothChildren(avl_node_t *node)
{
	return 	(HasChild(node, LEFT) && HasChild(node, RIGHT));
}

static int IsLeaf(avl_node_t *node)
{
	return (NULL == node->children[LEFT] && NULL == node->children[RIGHT]);
}

avl_t *AVLCreate(int (*is_before)(const void *lhs, const void *rhs))
{
	avl_t *tree = NULL;

	tree = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == tree)
	{
		return NULL;
	}

	tree->is_before = is_before;
	SetRoot(tree, NULL);

	return tree;
}

void AVLDestroy(avl_t *tree)
{
	assert(NULL != tree);

	if (!AVLIsEmpty(tree))
	{
		DestroyNodes(tree->root);
	}

	free(tree);
	tree = NULL;
}

static void DestroyNodes(avl_node_t *iter)
{
	if (NULL != iter)
	{
		DestroyNodes(GetChild(iter, LEFT));
		DestroyNodes(GetChild(iter, RIGHT));
		Remove(iter);
	}
}

static void Remove(avl_node_t *node)
{
	free(node);
	node = NULL;
}

size_t AVLSize(const avl_t *tree)
{	
	assert(NULL != tree);

	if (!AVLIsEmpty(tree))
	{
		return Count(tree->root);
	}
	
	return 0;
}

static size_t Count(avl_node_t *iter)
{
	if (NULL == iter)
	{
		return 0;
	}

	return Count(GetChild(iter, LEFT)) + Count(GetChild(iter, RIGHT)) + 1;
}

int AVLIsEmpty(const avl_t *tree)
{
	assert(NULL != tree);
	return (NULL == tree->root);
}

int AVLInsert(avl_t *tree, void *data)
{
	avl_node_t *new_node = NULL;

	assert(NULL != tree);

	new_node = CreateNode(data, 0, NULL, NULL);
	if (NULL == new_node)
	{
		return FAILURE;
	}

	if (AVLIsEmpty(tree))
	{
		tree->root = new_node;
		return SUCCESS;
	}

	SetRoot(tree, FindAndInsert(tree, tree->root, new_node, data));

	return SUCCESS;
}

static avl_node_t *CreateNode(
	void *data, 
	size_t height,
	avl_node_t *left_child, 
	avl_node_t *right_child
)
{
	avl_node_t *node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if (NULL == node)
	{
		return NULL;
	}

	InitNode(node, data, height, left_child, right_child);
		
	return node;
}

static void InitNode(
	avl_node_t *node,
	void *data, 
	size_t height,
	avl_node_t *left_child, 
	avl_node_t *right_child
)
{
	SetData(node, data);
	SetHeight(node, height);
	SetChild(node, left_child, LEFT);
	SetChild(node, right_child, RIGHT);
}

static avl_node_t *FindAndInsert(
	avl_t *tree,
	avl_node_t *iter,
	avl_node_t *new_node, 
	void *data
)
{
	int child_side = tree->is_before(GetData(iter), data);
	avl_node_t *child = GetChild(iter, child_side);

	if (NULL != child)
	{
		SetChild(iter
		, FindAndInsert(tree, child, new_node, data)
		, child_side);
	}

	if (NULL == child)
	{
		SetChild(iter, new_node, child_side);	
	}

	SetHeight(iter, UpdateHeight(iter));

	if (!IsBalanced(iter))
	{
		iter = Balance(iter);
	}

	return iter;
}

static int IsBalanced(avl_node_t *node)
{
	return IsLeaf(node) || 
		(HasBothChildren(node) && 
		CheckBalance(GetChild(node, LEFT), GetChild(node, RIGHT))) ||
		(0 == node->children[HasChild(node, LEFT)]->height);
}

static int CheckBalance(avl_node_t *lhs, avl_node_t *rhs)
{
	int lhs_height = lhs->height;
	int rhs_height = rhs->height;

	return (lhs_height - rhs_height <= 1 
		&& lhs_height - rhs_height >= -1);
}

static avl_node_t *Balance(avl_node_t *node)
{
	int side_case = GetCase(node);
	avl_node_t *child = GetChild(node, side_case);
	int side_side_case = GetCase(GetChild(node, side_case));
	avl_node_t *child_child = GetChild(child, side_side_case);

	if (side_case == side_side_case)
	{
		node->children[side_case] = GetChild(child, !side_case);
		child->children[!side_case] = node;

		SetHeight(node, UpdateHeight(node));
		SetHeight(child, UpdateHeight(child));

		return child;
	}

	node->children[side_case] = GetChild(child_child
					, side_side_case);
	child->children[side_side_case] = GetChild(child_child
					, side_case);
	child_child->children[side_case] = child;
	child_child->children[side_side_case] = node;

	SetHeight(node, UpdateHeight(node));
	SetHeight(child, UpdateHeight(child));
	SetHeight(child_child, UpdateHeight(child_child));

	return child_child;
}

static int GetCase(avl_node_t *node)
{
	avl_node_t *left_child = GetChild(node, LEFT);
	avl_node_t *right_child = GetChild(node, RIGHT);

	if (!HasBothChildren(node))
	{
		return HasChild(node, LEFT);
	}

	return (left_child->height > right_child->height);
}

static size_t UpdateHeight(avl_node_t *node)
{
	if (IsLeaf(node))
	{
		return 0;
	}
	else if (!HasBothChildren(node))
	{
		return node->children[HasChild(node, LEFT)]->height + 1;
	}

	return GetBiggestHeight(node) + 1;
}

static size_t GetBiggestHeight(avl_node_t *node)
{
	avl_node_t *left_child = GetChild(node, LEFT);
	avl_node_t *right_child = GetChild(node, RIGHT);

	return (GetHeight(left_child) > GetHeight(right_child)) ? 
		GetHeight(left_child) : GetHeight(right_child);
}

void AVLRemove(avl_t *tree, const void *data)
{
	assert(NULL != tree);

	if (AVLIsEmpty(tree))
	{
		return;
	}

	SetRoot(tree, FindAndRemove(tree, tree->root, data));
}

static avl_node_t *FindAndRemove(avl_t *tree, avl_node_t *iter, const void *data)
{
	int child_side = tree->is_before(GetData(iter), data);
	avl_node_t *child = GetChild(iter, child_side);

	if (NULL != child && !IsMatch(GetData(iter), data, tree->is_before))
	{
		SetChild(iter, FindAndRemove(tree, child, data), child_side);

		SetHeight(iter, UpdateHeight(iter));

		if (!IsBalanced(iter))
		{
			iter = Balance(iter);
		}	
	}

	if (IsMatch(GetData(iter), data, tree->is_before))
	{
		iter = UpdateChildrenAndRemove(iter);
	}
	
	return iter;
}

static int IsMatch(
	const void *lhs, 
	const void *rhs, 
	int (*is_before)(const void *lhs, const void *rhs)
)
{
	return (is_before(lhs, rhs) == is_before(rhs, lhs));	
}

static avl_node_t *UpdateChildrenAndRemove(avl_node_t *iter)
{
	static avl_node_t *first_iter = NULL;

	if (NULL == first_iter)
	{
		first_iter = iter;
		if (HasBothChildren(iter))
		{
			iter = UpdateChildrenAndRemove(GetChild(iter, RIGHT));
		}
		else
		{
			avl_node_t *temp = GetChild(iter, HasChild(iter, LEFT));
			Remove(iter);
			iter = temp;
			temp = NULL;
		}
		first_iter = NULL;
	}
	else
	{
		if (HasChild(iter, LEFT))
		{
			avl_node_t *left_child = GetChild(iter, LEFT);
			SetChild(iter, UpdateChildrenAndRemove(left_child), LEFT);
		}
		else
		{
			SetChild(iter, GetChild(first_iter, LEFT), LEFT);
			Remove(first_iter);
		}

		SetHeight(iter, UpdateHeight(iter));

		if (!IsBalanced(iter))
		{
			iter = Balance(iter);
		}
	}

	return iter;
}

size_t AVLHeight(const avl_t *tree)
{
	if (AVLIsEmpty(tree))
	{
		return -1;
	}

	return tree->root->height;
}

void *AVLFind(const avl_t *tree, void *data)
{
	assert(NULL != tree);

	if (AVLIsEmpty(tree))
	{
		return NULL;
	}

	return Find(tree->is_before, tree->root, data);
}

static void *Find(
	int (*is_before)(const void *lhs, const void *rhs),
	avl_node_t *iter,
	void *data
)
{
	int child_side = is_before(GetData(iter), data);
	avl_node_t *child = GetChild(iter, child_side);

	if (IsMatch(GetData(iter), data, is_before))
	{
		return GetData(iter);
	}

	if (NULL == child)
	{
		return NULL;
	}
	
	return Find(is_before, child, data);
}

int AVLForEach(
	avl_t *tree,
	int (*action)(void *data, void *params),
	void *params
)
{
	int check = SUCCESS;

	assert(NULL != tree && NULL != action);

	if (AVLIsEmpty(tree))
	{
		return FAILURE;
	}

	check = PerformAction(tree->root, action, params);

	return check;
}

static int PerformAction(
	avl_node_t *iter, 
	int (*action)(void *data, void *params),
	void *params
)
{
	int check = action(GetData(iter), params);	

	if (SUCCESS == check && HasChild(iter, LEFT))
	{
		PerformAction(GetChild(iter, LEFT), action, params);
	}

	if (SUCCESS == check && HasChild(iter, RIGHT))
	{
		PerformAction(GetChild(iter, RIGHT), action, params);
	}

	return check;
}
