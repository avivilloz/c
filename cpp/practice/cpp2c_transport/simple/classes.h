#ifndef __CLASSES_H__
#define __CLASSES_H__

typedef struct X X;
typedef struct Y_raw Y_raw;
typedef struct Y Y;
typedef struct D D;
typedef struct vt_y vt_y;
typedef struct vt_d vt_d;

struct X
{
	int m_num;
};

struct Y_raw
{
	X m_x;
	int m_a;
};

struct Y 
{
	Y_raw m_y;
	vt_y *m_vt;
};

struct D
{
	Y_raw m_y; /* hidden, because it is derived */
	X m_x;
	vt_d *m_vt;
};

struct vt_y
{
	void (*ydtor)(Y_raw *this);
	void (*foo)(Y *y);
};

struct vt_d
{
	void (*ydtor)(Y_raw *this);
	void (*foo)(Y *y);
	void (*dodo)(D *d);
};

void XCtor(X *this);
void XInitCtor(X *this, int num);
void XCCtor(X *this, X *src);
void XDtor(X *this);

void YCtor(Y *this);
void YRawDtor(Y_raw *this); 
void YDtor(Y *this);
void YFoo(Y *y);
void YBar(const Y *y);

void DCtor(D *this);
void DDtor(D *this);
void DDodo(D *d);

#endif /* __CLASSES_H__ */
