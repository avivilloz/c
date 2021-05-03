/****************************************************************************
Title: Slist Exercise - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Peter
Description: Exercise implementing Slists and nodes
****************************************************************************/

#include <stdio.h>	/*NULL*/
#include <assert.h>	/*assert*/
#include "slist_ex.h"	/*api*/
#include "slist.h"	/*api*/

struct slist_node
{
        void *data;            		
        struct slist_node *next;    	
};

/****************************************************************************/

slist_iter_t Flip(slist_iter_t head)
{
	slist_iter_t temp = head, temp2 = head->next, temp3 = temp2->next, previous_head = head;

	assert(NULL != head);

	/************************ NEXT POINTS TO THE PREVIOUS *************************/

	while (NULL != temp2->next)
	{
		if (NULL != temp3)
		{
			temp3 = temp2->next;
		}

		temp2->next = temp;	
		temp = temp2;
		temp2 = temp3;
	}

	/************************** HEAD EQUALS LAST BEFORE TAIL ***********************/
	
	head = temp;

	/************************ PREVIOUS HEAD POINTS TO TAIL *************************/

	previous_head->next = temp2;

	return head;
}

/****************************************************************************/

int HasLoop(const slist_iter_t head)
{
	slist_iter_t runner1 = (slist_iter_t)head, runner2 = head->next;

	assert(NULL != head);

	/************************** CHECKS IF THERE IS LOOP ***********************/

	while (NULL != runner2 && NULL != runner2->next && runner2 != runner1)  
	{	
		runner1 = runner1->next;
		runner2 = runner2->next->next;
	}

	return	(runner1 == runner2);
}

/****************************************************************************/

slist_iter_t FindIntersection(slist_iter_t head1, slist_iter_t head2)
{
	slist_iter_t runner1 = head1, runner2 = head2;

	assert(NULL != head1 && NULL != head2);

	/************************** CHECKS IF LISTS INTERSECT ***********************/

	for (; NULL != runner1->next; runner1 = runner1->next)
	{
		for (runner2 = head2; NULL != runner2->next; runner2 = runner2->next)
		{
			if(runner1 == runner2)
			{
				return runner1;
			}
		}	
	}

	return NULL;
}
