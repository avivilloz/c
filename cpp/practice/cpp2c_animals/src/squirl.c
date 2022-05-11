/*****************************************************************************
Title: cpp_to_c2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: cpp_to_c2
******************************************************************************/

#include "squirl.h"

/*****************************************************************************/

extern vtbl_animal_t g_vtbl_animal;
vtbl_squirl_t g_vtbl_squirl = {SquirlDtor, SquirlDisplay};

/*****************************************************************************/

void SquirlCtor(squirl_t *this)
{
	AnimalCtor((animal_t *)this);
	this->vtbl = &g_vtbl_squirl;
	printf("Squirl::Ctor()\n");
}

void SquirlDtor(squirl_t *this)
{
	this->vtbl = (vtbl_squirl_t *)&g_vtbl_animal;
	printf("Squirl::dtor()\n");
	AnimalDtor((animal_t *)this);
}

void SquirlCCtor(squirl_t *this, const squirl_t *other)
{
	AnimalCCtor((animal_t *)this, (animal_t *)other);
	this->vtbl = other->vtbl;
	printf("Squirl::CCtor()\n");
}

void SquirlDisplay(const squirl_t *this)
{
	printf("Squirl::Display() ID:%d\n", GetId((animal_t *)this));
}

/*****************************************************************************/
