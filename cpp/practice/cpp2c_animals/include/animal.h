/*****************************************************************************
Title: cpp_to_c2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: cpp_to_c2
******************************************************************************/

#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include <stdio.h>

/*****************************************************************************/

typedef struct vtbl_animal vtbl_animal_t;
typedef struct raw_animal raw_animal_t;
typedef struct animal animal_t;

struct vtbl_animal
{
	void (*dtor)(animal_t *this);
	void (*display)(const animal_t *this);
};

struct raw_animal
{
	int id;
};

struct animal
{
	vtbl_animal_t *vtbl;
	raw_animal_t dms_animal;
};

/*****************************************************************************/

void AnimalCtor(animal_t *this);
void AnimalDtor(animal_t *this);
void AnimalCCtor(animal_t *this, const animal_t *other);
void AnimalDisplay(const animal_t *this);
void PrintCount(void);
int GetId(const animal_t *this);

/*****************************************************************************/

#endif /* __ANIMAL_H__ */

/*****************************************************************************/
