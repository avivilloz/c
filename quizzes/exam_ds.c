/*****************************************************************************/

/* DS-exam 10/09/2020 Aviv Illoz */

/*****************************************************************************/
/* Ex1  */ 

/* 1 */

/* using pointers instead of offsets */

typedef struct fsa_block
{
	fsa_t *fsa_header;
	fsa_b_t *next_free_b;
} fsa_b_t;

typedef struct fsa
{
	fsa_b_t *first_free_b;
} fsa_t;

static int IsLastBlock(fsa_b_t *block);

/******************************/

void *FSAAlloc(fsa_t *fsa)
{
	fsa_b_t *block_header = NULL;
	void *new_block = NULL;

	assert(NULL != fsa);

	if (NULL == fsa->first_free_b)
	{
		return NULL;
	}

	block_header = fsa->first_free_b;
	new_block = (void *)(block_header + 1);

	if (IsLastBlock(block_header))
	{
		fsa->first_free_b = NULL;
	}
	else
	{
		fsa->first_free_b = fsa->first_free_b->next_free_b;
	}

	block_header->next_free_b = NULL;

	return new_block;
}

static int IsLastBlock(fsa_b_t *block)
{
	return (block->next_free_b == block);
}

/******************************/

void FSAFree(void *block)
{
	fsa_b_t *block_header = (fsa_b_t *)block - 1;

	assert(NULL != block_header);

	if (NULL == block_header->next_free_b)
	{
		fsa_t *fsa = block_header->fsa_header;
			
		if (NULL == fsa->first_free_b)
		{
			block_header->next_free_b = block_header;	
		}
		else
		{
			block_header->next_free_b = fsa->first_free_b;
		}

		fsa_first_free_b = block;
	}
}

/******************************/
/* 2 */

/* when creating the buffer, one additional feature to add is a vsa_block 
in the end with size 0 and is_free flag always set to 0, so that we know 
that we reached the end */

typedef struct vsa_block
{
	size_t block_size;
	int is_free;
} vsa_b_t;

typedef struct vsa
{
	vsa_b_t *first_block_header;
} vsa_t;

#define BLOCK_HEADER_SIZE (sizeof(vsa_b_t))
#define MINIMUM_BLOCK_SIZE (sizeof(size_t))

static int IsEndOfBuffer(vsa_b_t *block);
static size_t NextBlock(vsa_b_t *block);
static vsa_b_t *GetNextBlock(vsa_b_t *block);
static void MergeBlocks(vsa_b_t *block);
static void AllocateBlock(vsa_b_t *block, size_t desired_size);
static int IsEnoughForAnotherBlock(size_t block_size, size_t desired_size);

/******************************/
/* SEBASTIAN: 	Nice and short implementation of the VSA! I like that you use 
				pointers, it makes it much easier.
*/
void *VSAAlloc(vsa_t *vsa, size_t desired_size)
{
	vsa_b_t *curr_block = NULL;

	assert(NULL != vsa);

	for (curr_block = vsa->first_block_header; 
		 !IsEndOfBuffer(curr_block);
		 curr_block = GetNextBlock(curr_block))
	{
		if (curr_block->is_free)
		{
			MergeBlocks(curr_block);
			if (curr_block->block_size >= desired_size)
			{
				AllocateBlock(curr_block, desired_size);
				return curr_block;
			}
		}
	} 

	return NULL; 
}

static int IsEndOfBuffer(vsa_b_t *block)
{
	return (0 == block->block_size);
}

static size_t NextBlock(vsa_b_t *block)
{
	return (block->block_size + BLOCK_HEADER_SIZE);
}

static vsa_b_t *GetNextBlock(vsa_b_t *block)
{
	return (vsa_b_t *)((char *)block + NextBlock(block));
}

static void MergeBlocks(vsa_b_t *block)
{
	vsa_b_t *curr_block = GetNextBlock(block);
	
	for (; curr_block->is_free; curr_block = GetNextBlock(block))
	{
		block->block_size += NextBlock(curr_block);
	}
}

static void AllocateBlock(vsa_b_t *block, size_t desired_size)
{
	block->is_free = 0;

	if (IsEnoughForAnotherBlock(block->block_size, desired_size))
	{
		vsa_b_t *new_block = NULL;
		size_t new_b_size = block_size - desired_size - BLOCK_HEADER_SIZE;

		block->block_size = desired_size;

		new_block = GetNextBlock(block);
		new_block->block_size = new_b_size;
		new_block->is_free = 1;
	}
}

static int IsEnoughForAnotherBlock(size_t block_size, size_t desired_size)
{
	return ((BLOCK_HEADER_SIZE + MINIMUM_BLOCK_SIZE) >= 
		    (block_size - desired_size));
}

/******************************/

void VSAFree(void *block)
{
	vsa_b_t *block_header = (vsa_b_t *)((char *)block - BLOCK_HEADER_SIZE);

	assert(NULL != block_header);

	block_header->is_free = 1;
}

/******************************/
/* 3 */

/* 
when creating the FSA buffer, the programmer has to be sure to include 
one function of alignment. the user would send to the create function the desired 
size of the buffer, the programmer has to be sure each block will be alligned 
in memory from advance. this is done by first checking if buffer_size % alignment
condition (sizeof(size_t)) equals 0, if not, it should be increased to the first 
bigger size which is aligned:
	
	buffer_size += sizeof(size_t) - (buffer_size % sizeof(size_t));

the same applies to VSA, the difference is that everytime we allocate for VSA we 
need to align the new block_size (desired size by the user) to a bigger alligned 
size.
*/

/*****************************************************************************/
/* Ex2 */

typedef struct node
{
	void *data;
	node_t *next;
} node_t;

node_t *FlipList(node_t *head)
{
	node_t *curr = head;
	node_t *next = curr->next;
	node_t *temp = NULL;

	curr->next = NULL;

	while (NULL != next)
	{
		temp = next->next;
		next->next = curr;
		curr = next;
		next = temp;
	}

	return curr;
}

/*****************************************************************************/
/* Ex3 */

/* 1 */

/* O(N) */

/******************************/
/* functions for part 2 and 3 could be done in one function, (i.e to check and 
open loop, or to check and remove intersection), but since the requirement is to 
create both so i included one inside the other, i.e i check inside the open or 
remove functions */

/* 2 */

static int HasLoop(node_t *head)
{
	node_t *fast_r = head->next;
	node_t *slow_r = head;

	for (; fast_r != slow_r && 
		   fast_r->next != slow_r && 
		   NULL != fast_r &&
		   NULL != fast_r->next;
		   fast_r = fast_r->next->next,
		   slow_t = slow_r->next)
	{}

	return (fast_r == slow_r || fast_r->next == slow_r);  
}

/******************************/

/* SEBASTIAN: 	I tried compiling this one and testing it and besides some minor
				syntax details the code didnt run.
				Soething in the logic of the loop isnt working
*/
void OpenLoop(node_t *head)
{
	if (HasLoop(head))
	{
		node_t *node_to_open = head;
		node_t *fast_r = head->next;
		node_t *slow_r = head;

		while (fast_r->next != node_to_open && fast_r->next->next != node_to_open)
		{
			/* SEBASTIAN: I dont get this condition here 
						You initialize the variable node_to_open to head,
						and never change it so when is it gonna become different
						than head?
						Also head is never changed so i dont see this condition
						ever happening
			*/
			if (node_to_open != head)
			{
				node_to_open = node_to_open->next;
			}

			for (fast_r = node_to_open->next
				 slow_r = node_to_open; 
				 fast_r != slow_r && 
				 fast_r->next != slow_r &&
				 fast_r->next != node_to_open &&
				 fast_r->next->next != node_to_open; 
				 fast_r = fast_r->next->next,
				 slow_t = slow_r->next)
			{}
		}

		if (fast_r->next != node_to_open)
		{
			fast_r->next = NULL;
		} 
		else if (fast_r->next->next != node_to_open)
		{
			fast_r->next->next = NULL;
		}
	}
}

/******************************/

/* fixed: */

void OpenLoop(node_t *head)
{
	node_t *node_to_open = NULL;
	node_t *fast_r = NULL;
	node_t *slow_r = NULL;

	if (!HasLoop(head))
	{
		return;
	}

	node_to_open = head;
	fast_r = head->next;
	slow_r = head;

	for (; ; node_to_open = node_to_open->next)
	{
		for (fast_r = node_to_open->next,
			 slow_r = node_to_open; 
			 fast_r != slow_r && 
			 fast_r->next != slow_r;
			 fast_r = fast_r->next->next,
			 slow_t = slow_r->next)
		{
			if (fast_r->next == node_to_open)
			{
				fast_r->next = NULL;
				return;
			} 
			else if (fast_r->next->next == node_to_open)
			{
				fast_r->next->next = NULL;
				return;
			}
		}
	}
}


/******************************/
/* 3 */

/* SEBASTIAN: 	This one dint compile either. Some syntax problems.
				When i tried to fix them the execution got stuck too.
				Also a little hard to follow because of the naming of the
				variables.
				This one seems to have a complexity of O(n2) and it can be done
				in just O(n) complexity.
				Let me know if you want me to explain to you how.
*/
static int HasIntersection(node_t *l1_head, node_t *l2_head)
{
	node_t *l1_r = l1_head;
	node_t *l2_r = l2_head;

	while (NULL != l1_r && l1_r != l2_r)
	{
		if (l1_r != l1_head)
		{
			l1_r = l1->next;
		}

		for (l2_r = l2_head; NULL != l2_r && l2_r != l1_r; l2_r = l2->next)
		{} 
	}

	return (l1_r == l2_r);
}

/******************************/

void RemoveIntersection(node_t *l1_head, node_t *l2_head)
{
	if (HasIntersection(l1_head, l2_head)
	{
		while (NULL != l1_r && l1_r->next != l2_r)
		{
			if (l1_r != l1_head)
			{
				l1_r = l1->next;
			}

			for (l2_r = l2_head; NULL != l2_r && l2_r != l1_r->next; l2_r = l2->next)
			{} 
		}

		l1_head->next = NULL;
	}
}

/******************************/

/* fixed: */

/* O(n^2) */

void RemoveIntersection(node_t *l1_head, node_t *l2_head)
{
	node_t *l1_curr = NULL;
	node_t *l2_curr = NULL;

	if (!HasIntersection(l1_head, l2_head)
	{
		return;
	}

	l1_curr = l1_head;
	l2_curr = l2_head;
	
	for (; ; l1_curr = l1_curr->next)
	{
		for (l2_curr = l2_head; NULL != l2_curr; l2_curr = l2_curr->next)
		{
			if (l2_curr == l1_curr->next)
			{
				l1_curr->next = NULL;
				return;
			}
		} 
	}
}

/*****************************************************************************/
/* Ex4 */

typedef struct slist_iter
{
	node_t *node;
} slist_iter_t;

static node_t *IterToNode(slist_iter_t iter);

/******************************/

/* SEBASTIAN: 	I think its cool hat youre using iter, but its implementation
				details that can be omitted.
*/
slist_iter_t SListRemove(slist_iter_t iter)
{
	node_t *node_to_return = IterToNode(iter);
	node_t *node_to_remove = NULL;

	if (NULL == node_to_return || NULL == node_to_return->next)
	{
		return iter;
	}

	node_to_remove = node_to_return->next;

	node_to_return->data = node_to_remove->data;
	node_to_return->next = node_to_remove->next;

	free(node_to_remove);
	node_to_remove = NULL;

	return iter;
}

static node_t *IterToNode(slist_iter_t iter)
{
	return iter.node;
}

/*****************************************************************************/
/* Ex5 */

typedef struct dlist_node
{
	void *data;
	dlist_node_t *next;
	dlist_node_t *prev;
} dlist_node_t;

typedef struct dlist_iter
{
	dlist_node_t *node;
} dlist_iter_t;

dlist_node_t *IterToNode(dlist_iter_t iter);
dlist_iter_t NodeToIter(dlist_node_t *node);

/******************************/
/* SEBASTIAN: 	Also good logic but same comment as before, i dont think iterators
				is needed to resolve this exercises.
*/
dlist_iter_t DListInsert(dlist_iter_i iter, void *data)
{
	dlist_node_t *node = IterToNode(iter);
	dlist_node_t *new_node = (dlist_node_t *)malloc(sizeof(dlist_node_t));
	if (NULL == new_node)
	{
		return ;
	}

	new_node->data = data;
	new_node->next = node;
	new_node->prev = node->prev;

	node->prev = new_node;

	return NodeToIter(new_node);
}

dlist_node_t *IterToNode(dlist_iter_t iter)
{
	return iter.node;
}

dlist_iter_t NodeToIter(dlist_node_t *node)
{
	dlist_iter_t iter;
	iter->node = node;

	return iter;
}

/******************************/

dlist_iter_t DListRemove(dlist_iter_t iter)
{
	dlist_node_t *node_to_remove = IterToNode(iter);
	dlist_iter_t iter_to_return = NodeToIter(node_to_remove->next);

	if (NULL == node_to_remove || NULL == node_to_remove->next)
	{
		return iter;
	}

	node_to_remove->next->prev = node_to_remove->prev;
	node_to_remove->prev->next = node_to_remove->next;

	free(node_to_remove);
	node_to_remove = NULL;

	return iter_to_return;
}

/*****************************************************************************/
/* Ex6 */

int FindMissingNum(int arr[], size_t size, int biggest_num)
{
	int expected_sum = (biggest_num * (biggest_num + 1)) / 2;
	int sum = 0;
	size_t i = 0;

	for (; i < size; ++i)
	{
		sum += arr[i];
	}

	return expected_sum - sum;
}

/*****************************************************************************/
/* Ex7 */

/* if the bit is set on it means is part of shape, otherwise it is not */

/*****************************************************************************/
/* Ex8 */

/* assuming is not a circular queue */

#define Q_SIZE

typedef struct queue
{
	char queue[Q_SIZE];
	size_t num_of_elements;
	size_t first_element;
} queue_t;

/******************************/
/* SEBASTIAN: 	If i understand the logic correctly i think its good. You are
				protecting from pushing in a full queue which is correct.
				But we already have a variable in the struct whcih tells us
				the number of elements in the queue, and also we have the constant
				Q_SIZE, so comparing both i think would be enough.
				Also you miss to increase the num_of_element counter everytime
				you Push.
*/
void PushChar(queue_t *q, char c)
{
	size_t last_element = (q->first_element + q->num_of_elements) % Q_SIZE;

	if (last_element < q->first_element)
	{
		q->queue[last_element] = c;
		++q->num_of_elements;
	}
}

/******************************/

/* fixed: */

void PushChar(queue_t *q, char c)
{
	size_t last_element = (q->first_element + q->num_of_elements) % Q_SIZE;

	if (q->num_of_elements < Q_SIZE)
	{
		q->queue[last_element] = c;
		++q->num_of_elements;
	}
}

/******************************/

char PopChar(queue_t *q)
{
	char c = '\0';

	if (0 == q->num_of_elements)
	{
		return c;
	}

	c = q->queue[q->first_element];

	q->first_element = (q->first_element + 1) % Q_SIZE;
	--q->num_of_elements;

	return c;
}

/*****************************************************************************/
