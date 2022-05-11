/*****************************************************************************
Title: Der 
Description: learn Der
******************************************************************************/

#include "classes.h"

static vt_d dvt = {YRawDtor, YFoo, DDodo};

void DCtor(D *this)
{
	XCtor(&this->m_y.m_x);
	/* this->m_y.m_a = 0 */
	XCtor(&this->m_x);
	this->m_vt = &dvt;
}

void DDtor(D *this)
{
	XDtor(&this->m_x);
	this->m_vt->ydtor(&this->m_y);
}

void DDodo(D *d) {}

/*****************************************************************************/

