/*****************************************************************************
Title: cpp_to_c2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: cpp_to_c2
******************************************************************************/

#ifndef __CENTIPEDE_H__
#define __CENTIPEDE_H__

/*****************************************************************************/

#include "animal.h"

/*****************************************************************************/

typedef struct vtbl_centipede vtbl_centipede_t;
typedef struct raw_centipede raw_centipede_t;
typedef struct centipede centipede_t;

struct vtbl_centipede
{
	void (*dtor)(centipede_t *this);
	void (*display)(const centipede_t *this);
	void (*buy_shues)(const centipede_t *this);
};

struct raw_centipede
{
	int num_legs;
};

struct centipede
{
	vtbl_centipede_t *vtbl;
	raw_animal_t dms_animal;
	raw_centipede_t dms_centipede;
};

/*****************************************************************************/

void CentipedeCtor(centipede_t *this);
void CentipedeDtor(centipede_t *this);
void CentipedeCCtor(centipede_t *this, const centipede_t *other);
void CentipedeDisplay(const centipede_t *this);
void CentipedeBuyShues(const centipede_t *this);


/*****************************************************************************/

#endif /* __CENTIPEDE_H__ */

/*****************************************************************************/
