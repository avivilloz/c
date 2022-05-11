/*****************************************************************************
Title: cpp_to_c2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: cpp_to_c2
******************************************************************************/

#include <stdlib.h>

#include "lanimal.h"

/****************************************************************************/

extern vtbl_animal_t g_vtbl_animal;
vtbl_lanimal_t g_vtbl_lanimal = {LAnimalDtor, LAnimalDisplay};

/****************************************************************************/

static void ExitIfBad(int is_good)
{
	if (!is_good)
	{
		perror("error");
		exit(1);
	}
}

/****************************************************************************/

void LAnimalCtor(lanimal_t *this)
{
	animal_t *temp = NULL;

	AnimalCtor((animal_t *)this);
	this->vtbl = &g_vtbl_lanimal;

	temp = (animal_t *)malloc(sizeof(centipede_t));
	ExitIfBad(NULL != temp);
	CentipedeCtor((centipede_t *)temp);
	this->dms_lanimal.m_a1 = temp;

	temp = (animal_t *)malloc(sizeof(squirl_t));
	ExitIfBad(NULL != temp);
	SquirlCtor((squirl_t *)temp);
	this->dms_lanimal.m_a2 = temp;

	CentipedeCtor(&this->dms_lanimal.m_c);
	SquirlCtor(&this->dms_lanimal.m_sq);	
}

void LAnimalDtor(lanimal_t *this)
{
	this->dms_lanimal.m_a1->vtbl->dtor(this->dms_lanimal.m_a1);
	free(this->dms_lanimal.m_a1);
	this->dms_lanimal.m_a1 = NULL;

	this->dms_lanimal.m_a2->vtbl->dtor(this->dms_lanimal.m_a2);
	free(this->dms_lanimal.m_a2);
	this->dms_lanimal.m_a2 = NULL;

	SquirlDtor(&this->dms_lanimal.m_sq);
	CentipedeDtor(&this->dms_lanimal.m_c);

	this->vtbl = (vtbl_lanimal_t *)&g_vtbl_animal;
	AnimalDtor((animal_t *)this);
}

void LAnimalCCtor(lanimal_t *this, const lanimal_t *other)
{
	animal_t *temp = NULL;

	AnimalCCtor((animal_t *)this, (animal_t *)other);
	this->vtbl = other->vtbl;

	temp = (animal_t *)malloc(sizeof(centipede_t));
	ExitIfBad(NULL != temp);
	CentipedeCCtor((centipede_t *)temp, (centipede_t *)other->dms_lanimal.m_a1);
	this->dms_lanimal.m_a1 = temp;

	temp = (animal_t *)malloc(sizeof(squirl_t));
	ExitIfBad(NULL != temp);
	SquirlCCtor((squirl_t *)temp, (squirl_t *)other->dms_lanimal.m_a2);
	this->dms_lanimal.m_a2 = temp;

	CentipedeCCtor(&this->dms_lanimal.m_c, &other->dms_lanimal.m_c);
	SquirlCCtor(&this->dms_lanimal.m_sq, &other->dms_lanimal.m_sq);	
}

void LAnimalDisplay(const lanimal_t *this)
{
	this->dms_lanimal.m_a1->vtbl->display(this->dms_lanimal.m_a1);
	this->dms_lanimal.m_a2->vtbl->display(this->dms_lanimal.m_a2);

	CentipedeDisplay(&this->dms_lanimal.m_c);
	SquirlDisplay(&this->dms_lanimal.m_sq);
}

/****************************************************************************/
