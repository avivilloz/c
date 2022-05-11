/*****************************************************************************
Title: cpp_to_c2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: cpp_to_c2
******************************************************************************/

#include "general.h"

/*****************************************************************************/

void Foo1(const animal_t *animal)
{
	animal->vtbl->display(animal);
}

void Foo2(void)
{
	PrintCount();
}

animal_t Foo3(int i)
{
	centipede_t ret1;
	animal_t ret2;
	CentipedeCtor(&ret1);
	printf("Foo(int i)\n");
	CentipedeDisplay(&ret1);
	AnimalCCtor(&ret2, (animal_t *)&ret1);
	CentipedeDtor(&ret1);
	(void)i;
	return ret2;
}

void Fifi(centipede_t *c)
{
	centipede_t c2;
	CentipedeCCtor(&c2, c);
	CentipedeDisplay(&c2);
	CentipedeDtor(&c2);
}

/*****************************************************************************/
