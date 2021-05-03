/*****************************************************************************
* title: Josephus
* author: aviv illoz
* description: Solves the problem of josephus
******************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /*  malloc */

static int sword = 0, gather = 0;
static int *soldiers = NULL;	

int SetNumOfSoldiers(void);
void KillNext(void);
void KillFirst(void);

int main(void)
{	
	int rest = 0, diff = 0;
	rest = SetNumOfSoldiers();

	for (; rest > 1 ; diff = rest % 2, rest = rest / 2)
	{
		printf("-------------------------------%d soldiers left\n", rest);

		while (sword < rest + diff - 1)
		{	
			KillNext();
		}

		if (rest + diff - 1 == sword)
		{
			KillFirst();
		}

		else
		{
			sword = 0;
		}

		gather = 0;
	}

	printf("-------------------------------soldier %d is the winner!\n", soldiers[sword]);

	free(soldiers);

	return 0;
}

int SetNumOfSoldiers(void)
{
	int i = 0, j = 1;
	int num_of_soldiers = 0;

	printf("How many soldiers are in the circle?\n");

	scanf("%d", &num_of_soldiers); 

	soldiers = malloc(num_of_soldiers * sizeof(int));

	for (; i < num_of_soldiers; i++, j++)
	{
		soldiers[i] = j;
	}

	return num_of_soldiers;
}

void KillNext(void)	
{			
	printf("the sword is on soldier %d's hands\n", soldiers[sword]);

	printf("soldier %d killed soldier %d\n", soldiers[sword], soldiers[sword + 1]);

	soldiers[sword + 1] = 0;
		
	if(sword > 0)
	{
		gather++;

		soldiers[sword - gather] = soldiers[sword];			

		soldiers[sword] = 0;
	}

	sword += 2;
}

void KillFirst(void)
{
	printf("the sword is on soldier %d's hands\n", soldiers[sword]);

	printf("soldier %d killed soldier %d\n", soldiers[sword], soldiers[0]);

	gather++;

	soldiers[sword - gather] = soldiers[sword];			

	soldiers[0] = 0;

	sword = 1;
}
