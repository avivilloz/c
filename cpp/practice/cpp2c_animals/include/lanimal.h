/*****************************************************************************
Title: cpp_to_c2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: cpp_to_c2
******************************************************************************/

#ifndef __LEGENDARY_ANIMAL_H__
#define __LEGENDARY_ANIMAL_H__

/*****************************************************************************/

#include "animal.h"
#include "centipede.h"
#include "squirl.h"

/*****************************************************************************/

typedef struct vtbl_lanimal vtbl_lanimal_t;
typedef struct raw_lanimal raw_lanimal_t;
typedef struct lanimal lanimal_t;

struct vtbl_lanimal
{
	void (*dtor)(lanimal_t *this);
	void (*display)(const lanimal_t *this);	
};

struct raw_lanimal
{
	animal_t *m_a1;
	animal_t *m_a2;
	centipede_t m_c;
	squirl_t m_sq;
};

struct lanimal
{
	vtbl_lanimal_t *vtbl;
	raw_animal_t dms_animal; 
	raw_lanimal_t dms_lanimal; 
};

/*****************************************************************************/

void LAnimalCtor(lanimal_t *this);
void LAnimalCCtor(lanimal_t *this, const lanimal_t *other);
void LAnimalDtor(lanimal_t *this);
void LAnimalDisplay(const lanimal_t *this);

/*****************************************************************************/

#endif /* __LEGENDARY_ANIMAL_H__ */

/*****************************************************************************/
