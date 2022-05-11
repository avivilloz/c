/*****************************************************************************
Title: cpp_to_c2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: cpp_to_c2
******************************************************************************/

#include "centipede.h"

/*****************************************************************************/

extern vtbl_animal_t g_vtbl_animal;
vtbl_centipede_t g_vtbl_centipede = {CentipedeDtor, CentipedeDisplay, 
									CentipedeBuyShues};

/*****************************************************************************/

void CentipedeCtor(centipede_t *this)
{
	AnimalCtor((animal_t *)this);
	this->vtbl = &g_vtbl_centipede;
	this->dms_centipede.num_legs = 46;
	printf("Centipede::Ctor()\n");
}

void CentipedeDtor(centipede_t *this)
{
	this->vtbl = (vtbl_centipede_t *)&g_vtbl_animal;
	printf("Centipede::dtor()\n");
	AnimalDtor((animal_t *)this);
}

void CentipedeCCtor(centipede_t *this, const centipede_t *other)
{
	AnimalCCtor((animal_t *)this, (animal_t *)other);
	this->vtbl = other->vtbl;
	this->dms_centipede.num_legs = other->dms_centipede.num_legs;
	printf("Centipede::CCtor()\n");
}

void CentipedeDisplay(const centipede_t *this)
{
	printf("Centipede::Display() ID:%d  num legs:%d\n", 
			GetId((animal_t *)this), this->dms_centipede.num_legs);
}

#define ANIMAL_TYPE
void CentipedeBuyShues(const centipede_t *this)
{
	printf("Centipede::BuyShues() ID:%d\n", GetId((animal_t *)this));
}

/*****************************************************************************/
