/*****************************************************************************
Title: Y 
Description: learn Y
******************************************************************************/

#include "classes.h"

static vt_y yvt = {YRawDtor, YFoo};

void YCtor(Y *this)
{
	XCtor(&this->m_y.m_x);
	/* this->m_y.m_a = 0 */
	this->m_vt = &yvt;
}

void YRawDtor(Y_raw *this) 
{
	XDtor(&this->m_x);
}

void YDtor(Y *this)
{
	this->m_vt->ydtor(&this->m_y);
}

void YFoo(Y *y) {}
void YBar(const Y *y) {} 

/*****************************************************************************/

