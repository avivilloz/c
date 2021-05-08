#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct slist_node slist_node_t;

struct slist_node
{
	void *data;
	slist_node_t *next;
};

typedef struct slist
{
	slist_node_t *head;
} slist_t;


void OpenLoop(slist_t *list)
{
	slist_node_t *r1 = NULL;
	slist_node_t *r2 = NULL;
	slist_node_t *r3 = NULL;

	assert(NULL != list);

/*
	if (!HasLoop(list))
	{
		return;
	}
*/

	r1 = list->head;
	r2 = r1->next;
	r3 = r1;

	for (; r1 != r2->next && r1 != r2->next->next; r1 = r1->next)
	{
		r2 = r1->next;
		r3 = r1;
		for (; r2 != r3 && r1 != r2->next && r1 != r2->next->next; 
			   r2 = r2->next->next, r3 = r3->next)
		{}
	}

	if (r1 == r2->next)
	{
		r2->next = NULL;
	}
	else
	{
		r2->next->next = NULL;
	}
}

int main(void)
{
	slist_t *list = malloc(sizeof(slist_t));
	slist_node_t *n1 = malloc(sizeof(slist_node_t));
	slist_node_t *n2 = malloc(sizeof(slist_node_t));
	slist_node_t *n3 = malloc(sizeof(slist_node_t));
	slist_node_t *n4 = malloc(sizeof(slist_node_t));
	slist_node_t *n5 = malloc(sizeof(slist_node_t));
	slist_node_t *n6 = malloc(sizeof(slist_node_t));	
	slist_node_t *iter = NULL;	
	int array[6] = {1,2,3,4,5,6};
	size_t i = 0;

	list->head = n1;
	n1->data = &array[0];
	n1->next = n2;
	n2->data = &array[1];
	n2->next = n3;
	n3->data = &array[2];
	n3->next = n4;
	n4->data = &array[3];
	n4->next = n5;
	n5->data = &array[4];
	n5->next = n6;
	n6->data = &array[5];
	n6->next = n4;
	iter = list->head;

	for (; i < 8; ++i)
	{
		printf("%d ", *(int *)iter->data);
		iter = iter->next;
	}
	putchar('\n');
		
	OpenLoop(list);

	for (i = 0, iter = list->head; NULL != iter && i < 8; ++i)
	{
		printf("%d ", *(int *)iter->data);
		iter = iter->next;
	}
	putchar('\n');

	return 0;
}
