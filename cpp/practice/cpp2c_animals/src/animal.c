/*****************************************************************************
Title: cpp_to_c2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: cpp_to_c2
******************************************************************************/

#include "animal.h"

/*****************************************************************************/

static int g_count = 0;
vtbl_animal_t g_vtbl_animal = {AnimalDtor, AnimalDisplay};

/*****************************************************************************/

void AnimalCtor(animal_t *this)
{
	this->vtbl = &g_vtbl_animal;
	++g_count;
	this->dms_animal.id = g_count;
	printf("Animal::Ctor()%d\n", GetId(this));
}

void AnimalDtor(animal_t *this)
{
	--g_count;
	printf("Animal::Dtor()%d\n", GetId(this));
}

void AnimalCCtor(animal_t *this, const animal_t *other)
{
	this->vtbl = other->vtbl;
	++g_count;	
	this->dms_animal.id = g_count;
	printf("Animal::CCtor() %d\n", GetId(this));
}

void AnimalDisplay(const animal_t *this)
{
	printf("Animal::Display() : %d\n", GetId(this));
}

void PrintCount(void)
{
	printf("s_count: %d\n", g_count);
}

int GetId(const animal_t *this)
{
	return this->dms_animal.id;
}

/*****************************************************************************/
