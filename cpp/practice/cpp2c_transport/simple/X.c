/*****************************************************************************
Title: X 
Description: learn X
******************************************************************************/

#include "classes.h"

static int XGetNum(X *x);
static void XSetNum(X *x, int num);

void XCtor(X *this)
{
	XSetNum(this, 0);
}

void XInitCtor(X *this, int num)
{
	XSetNum(this, num);
}

void XCCtor(X *this, X *src)
{
	XSetNum(this, XGetNum(src));
}

void XDtor(X *this) {}

static int XGetNum(X *x)
{
	return x->m_num;
}

static void XSetNum(X *x, int num)
{
	x->m_num = num;
}

/*****************************************************************************/

