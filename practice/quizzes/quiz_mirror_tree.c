#include <stdio.h>
#include "bs_tree.h"

/* gd quiz_mirror_tree.c ../ds/bs_tree/src/bs_tree.c -I ../ds/bs_tree/include/ -o test */

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

static int IsBefore(const void *lhs, const void *rhs)
{
	return (*(int *)lhs > *(int *)rhs);
}

static int IsBeforeOposite(const void *lhs, const void *rhs)
{
	return (*(int *)lhs < *(int *)rhs);
}

static bst_t *MirrorTree(bst_t *tree)
{
	bst_t *mirror_tree = BSTCreate(IsBeforeOposite);
	bst_iter_t root;
	root.node = tree->stub.children[LEFT];

	for (; !BSTIsEmpty(tree)
		; BSTRemove(root)
		, root.node = tree->stub.children[LEFT])
	{
		BSTInsert(mirror_tree, BSTGetData(root));
	}

	BSTDestroy(tree);

	return mirror_tree;
}

int main(void)
{
	bst_t *tree = BSTCreate(IsBefore);
	bst_iter_t iter;
	int array[5] = {4,5,2,3,1};
	size_t i = 0;

	for (; i < 5; ++i)
	{
		BSTInsert(tree, &array[i]);
	}

	tree = MirrorTree(tree);

	printf("%d\n", BSTIsEmpty(tree));

	for (iter = BSTBegin(tree)
		; !BSTIterIsEqual(iter, BSTEnd(tree))
		; iter = BSTNext(iter))
	{
		printf("%d ", *(int *)BSTGetData(iter));
	}
	printf("\n");

	BSTDestroy(tree);

	return 0;
}

