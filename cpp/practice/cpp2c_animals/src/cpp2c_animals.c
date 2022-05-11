/*****************************************************************************
Title: cpp_to_c2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: cpp_to_c2
******************************************************************************/

#include <stdlib.h> /* malloc, free */

#include "animal.h"
#include "centipede.h"
#include "squirl.h"
#include "general.h"
#include "lanimal.h"

/*****************************************************************************/

static void ExitIfBad(int is_good)
{
	if (!is_good)
	{
		perror("error");
		exit(1);
	}
}

/*****************************************************************************/

int main(void)
{
	int i = 0;
	animal_t a1;
	animal_t *array1[3];
	animal_t array2[3];
	centipede_t c1;
	centipede_t c2;
	centipede_t array3[4];
	squirl_t *array4;
	lanimal_t *la1;
	lanimal_t *la2;

	CentipedeCtor(&c1);
	Foo1((animal_t*)&c1);

	a1 = Foo3(3);
	AnimalDisplay(&a1);
	AnimalDtor(&a1);

	Fifi(&c1);
	
	array1[0] = malloc(sizeof(centipede_t));
	ExitIfBad(NULL != array1[0]);
	CentipedeCtor((centipede_t *)array1[0]);
	
	array1[1] = malloc(sizeof(squirl_t));
	ExitIfBad(NULL != array1[1]);
	SquirlCtor((squirl_t *)array1[1]);

	array1[2] = malloc(sizeof(centipede_t));
	ExitIfBad(NULL != array1[2]);
	CentipedeCtor((centipede_t *)array1[2]);

	for (i = 0; i < 3; ++i)
	{
		array1[i]->vtbl->display(array1[i]);
	}

	for (i = 0; i < 3; ++i)
	{
		array1[i]->vtbl->dtor(array1[i]);
		free(array1[i]);
	}

	{
		centipede_t temp;

		CentipedeCtor(&temp);
		AnimalCCtor(&array2[0], (animal_t *)&temp);
		CentipedeDtor(&temp);
	}

	{
		squirl_t temp;

		SquirlCtor(&temp);
		AnimalCCtor(&array2[1], (animal_t *)&temp);
		SquirlDtor(&temp);
	}

	AnimalCtor(&array2[2]);

	for (i = 0; i < 3; ++i)
	{
		AnimalDisplay(&array2[i]);
	}

	/**************************/
	PrintCount();
	CentipedeCtor(&c2);
	PrintCount();

	/**************************/
	for (i = 0; i < 4; ++i)
	{
		CentipedeCtor(&array3[i]);
	}

	/*************************/
	array4 = (squirl_t *)malloc(4 * sizeof(squirl_t));
	ExitIfBad(NULL != array4);

	for (i = 0; i < 4; ++i)
	{
		SquirlCtor(&array4[i]);
	}

	for (i = 3; i >= 0; --i)
	{
		SquirlDtor(&array4[i]);
	}

	free(array4);

	/*************************/
	la1 = (lanimal_t *)malloc(sizeof(lanimal_t));
	ExitIfBad(NULL != la1);
	la2 = (lanimal_t *)malloc(sizeof(lanimal_t));
	ExitIfBad(NULL != la2);

	LAnimalCtor(la1);
	LAnimalCCtor(la2, la1);

	LAnimalDisplay(la1);
	LAnimalDisplay(la2);

	LAnimalDtor(la1);
	free(la1);
	la1 = NULL;

	LAnimalDisplay(la2);
	LAnimalDtor(la2);
	free(la2);
	la2 = NULL;

	printf("					end of test\n");

	/**************************************************/

	for (i = 3; i >= 0; --i)
	{
		CentipedeDtor(&array3[i]);
	}
	
	CentipedeDtor(&c2);

	for (i = 2; i >= 0; --i)
	{
		AnimalDtor(&array2[i]);
	}

	CentipedeDtor(&c1);

	return 0;
}

/*****************************************************************************/
