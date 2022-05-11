/*****************************************************************************
Title: cpp_to_c2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: cpp_to_c2
******************************************************************************/

#ifndef __SQUIRL_H__
#define __SQUIRL_H__

/*****************************************************************************/

#include "animal.h"

/*****************************************************************************/

typedef struct vtbl_squirl vtbl_squirl_t;
typedef struct squirl squirl_t;

struct vtbl_squirl
{
	void (*dtor)(squirl_t *this);
	void (*display)(const squirl_t *this);
};

struct squirl
{
	vtbl_squirl_t *vtbl;
	raw_animal_t dms_animal;
};

/*****************************************************************************/

void SquirlCtor(squirl_t *this);
void SquirlDtor(squirl_t *this);
void SquirlCCtor(squirl_t *this, const squirl_t *other);
void SquirlDisplay(const squirl_t *this);


/*****************************************************************************/

#endif /* __SQUIRL_H__ */

/*****************************************************************************/
