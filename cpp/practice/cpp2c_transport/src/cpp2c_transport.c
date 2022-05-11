/**************************************************************************
CPP TO C
**************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */

/**************************************************************************
Helper Functions 
**************************************************************************/

static void ExitIfBad(int is_good)
{
	if (!is_good)
	{
		perror("Error");
		exit(1);
	}
}

/**************************************************************************
Public Transport 
**************************************************************************/

typedef struct vtbl_pt vtbl_pt;
typedef struct public_transport_raw pt_raw;
typedef struct public_transport pt;

void PTCtor(pt *this);
void PTCCtor(pt *this, pt *other);
void PTDtor(pt *this);
void PrintCount(void);
void PTDisplay(const pt *this);
static void PTRawCtor(pt_raw *this);
static void PTRawCCtor(pt_raw *this, pt_raw *other);
static void PTRawDtor(pt_raw *this);
static int GetId(const pt_raw *this);

struct vtbl_pt
{
	void (*dtor)(pt *this);
	void (*display)(const pt *this);	
};

struct public_transport_raw
{
	int m_license_plate;
};

struct public_transport
{
	vtbl_pt *m_vtbl;
	pt_raw m_pt;
};

static int g_count = 0;
static vtbl_pt g_vtbl_pt = {PTDtor, PTDisplay};
	
void PTCtor(pt *this)
{
	this->m_vtbl = &g_vtbl_pt;
	PTRawCtor(&this->m_pt);
}

void PTCCtor(pt *this, pt *other)
{
	this->m_vtbl = other->m_vtbl;
	PTRawCCtor(&this->m_pt, &other->m_pt);
}

void PTDtor(pt *this)
{
	PTRawDtor(&this->m_pt);
}

void PTDisplay(const pt *this)
{
	printf("PublicTransport::display(): %d\n", GetId(&this->m_pt));
}

void PrintCount(void)
{
	printf("s_count: %d\n", g_count);
}

static void PTRawCtor(pt_raw *this)
{
	++g_count;
	this->m_license_plate = g_count;
	printf("PublicTransport::Ctor()%d\n", GetId(this));
}

static void PTRawCCtor(pt_raw *this, pt_raw *other)
{
	++g_count;
	this->m_license_plate = g_count;
	printf("PublicTransport::CCtor() %d\n", GetId(this));
	(void)other;
}

static void PTRawDtor(pt_raw *this)
{
	--g_count;
	printf("PublicTransport::Dtor()%d\n", GetId(this));
}

static int GetId(const pt_raw *this)
{
	return this->m_license_plate;
}

/**************************************************************************
Minibus 
**************************************************************************/

typedef struct vtbl_mb vtbl_mb;
typedef struct minibus_raw mb_raw;
typedef struct minibus mb;

void MBCtor(mb *this);
void MBCCtor(mb *this, mb *other);
void MBDtor(mb *this);
void MBDisplay(const mb *this);
void MBWash(const mb *this, int minutes);
static void MBRawCtor(mb_raw *this);
static void MBRawCCtor(mb_raw *this, mb_raw *other);
static void MBRawDtor(void);

struct vtbl_mb
{
	void (*dtor)(mb *this);
	void (*display)(const mb *this);	
	void (*wash)(const mb *this, int minutes);	
};

struct minibus_raw
{
	int m_num_seats;
};

struct minibus
{
	vtbl_mb *m_vtbl;
	pt_raw m_pt; 
	mb_raw m_mb; 
};

static vtbl_mb g_vtbl_mb = {MBDtor, MBDisplay, MBWash};

void MBCtor(mb *this)
{
	PTCtor((pt *)this);
	this->m_vtbl = &g_vtbl_mb;
	MBRawCtor(&this->m_mb);
}

void MBCCtor(mb *this, mb *other)
{
	PTCCtor((pt *)this, (pt *)other);
	this->m_vtbl = other->m_vtbl;
	MBRawCCtor(&this->m_mb, &other->m_mb);
}

void MBDtor(mb *this)
{
	MBRawDtor();
	this->m_vtbl = (vtbl_mb *)&g_vtbl_pt;
	PTDtor((pt *)this);
}

void MBDisplay(const mb *this)
{
	printf("Minibus::display() ID:%d", GetId(&this->m_pt));
	printf(" num seats:%d\n", this->m_mb.m_num_seats);
}

void MBWash(const mb *this, int minutes)
{
	printf("Minibus::wash(%d) ID:%d\n", minutes, GetId(&this->m_pt));
}

static void MBRawCtor(mb_raw *this)
{
	this->m_num_seats = 20;
	printf("Minibus::Ctor()\n");
}

static void MBRawCCtor(mb_raw *this, mb_raw *other)
{
	this->m_num_seats = other->m_num_seats;
	printf("Minibus::CCtor()\n");
}

static void MBRawDtor(void)
{
	printf("Minibus::Dtor()\n");
}

/**************************************************************************
Taxi 
**************************************************************************/

typedef struct vtbl_taxi vtbl_taxi;
typedef struct taxi taxi;

void TCtor(taxi *this);
void TCCtor(taxi *this, taxi *other);
void TDtor(taxi *this);
void TDisplay(const taxi *this);
static void TRawCtor(void);
static void TRawCCtor(void);
static void TRawDtor(void);

struct vtbl_taxi
{
	void (*dtor)(taxi *this);
	void (*display)(const taxi *this);	
};

struct taxi
{
	vtbl_taxi *m_vtbl;
	pt_raw m_pt; 
};

static vtbl_taxi g_vtbl_taxi = {TDtor, TDisplay};

void TCtor(taxi *this)
{
	PTCtor((pt *)this);
	this->m_vtbl = &g_vtbl_taxi;
	TRawCtor();
}

void TCCtor(taxi *this, taxi *other)
{
	PTCCtor((pt *)this, (pt *)other);
	this->m_vtbl = other->m_vtbl;
	TRawCCtor();
}

void TDtor(taxi *this)
{
	TRawDtor();
	this->m_vtbl = (vtbl_taxi *)&g_vtbl_pt;
	PTDtor((pt *)this);
}

void TDisplay(const taxi *this)
{
	printf("Taxi::display() ID:%d\n", GetId(&this->m_pt));
}

static void TRawCtor(void)
{
	printf("Taxi::Ctor()\n");
}

static void TRawCCtor(void)
{
	printf("Taxi::CCtor()\n");
}

static void TRawDtor(void)
{
	printf("Taxi::Dtor()\n");
}

/**************************************************************************
Special Taxi 
**************************************************************************/

typedef struct vtbl_st vtbl_st;
typedef struct special_taxi st;

void STCtor(st *this);
void STCCtor(st *this, st *other);
void STDtor(st *this);
void STDisplay(const st *this);
static void STRawCtor(void);
static void STRawCCtor(void);
static void STRawDtor(void);

struct vtbl_st
{
	void (*dtor)(st *this);
	void (*display)(const st *this);	
};

struct special_taxi
{
	vtbl_st *m_vtbl;
	pt_raw m_pt; 
};

static vtbl_st g_vtbl_st = {STDtor, STDisplay};

void STCtor(st *this)
{
	TCtor((taxi *)this);
	this->m_vtbl = &g_vtbl_st;
	STRawCtor();
}

void STCCtor(st *this, st *other)
{
	TCCtor((taxi *)this, (taxi *)other);
	this->m_vtbl = other->m_vtbl;
	STRawCCtor();
}

void STDtor(st *this)
{
	STRawDtor();
	this->m_vtbl = (vtbl_st *)&g_vtbl_taxi;
	TDtor((taxi *)this);
}

void STDisplay(const st *this)
{
	printf("SpecialTaxi::display() ID:%d", GetId(&this->m_pt));
}

static void STRawCtor(void)
{
	printf("SpecialTaxi::Ctor()\n");
}

static void STRawCCtor(void)
{
	printf("SpecialTaxi::CCtor()\n");
}

static void STRawDtor(void)
{
	printf("SpecialTaxi::Dtor()\n");
}

/**************************************************************************
Public Convoy 
**************************************************************************/

typedef struct vtbl_pc vtbl_pc;
typedef struct public_convoy_raw pc_raw;
typedef struct public_convoy pc;

void PCCtor(pc *this);
void PCCCtor(pc *this, pc *other);
void PCDtor(pc *this);
void PCDisplay(const pc *this);
static void PCRawCtor(pc_raw *this);
static void PCRawCCtor(pc_raw *this, pc_raw *other);
static void PCRawDtor(pc_raw *this);

struct vtbl_pc
{
	void (*dtor)(pc *this);
	void (*display)(const pc *this);	
};

struct public_convoy_raw
{
	pt *m_pt1;
	pt *m_pt2;
	mb m_mb;
	taxi m_taxi;
};

struct public_convoy
{
	vtbl_pc *m_vtbl;
	pt_raw m_pt; 
	pc_raw m_pc; 
};

static vtbl_pc g_vtbl_pc = {PCDtor, PCDisplay};

void PCCtor(pc *this)
{
	PTCtor((pt *)this);
	this->m_vtbl = &g_vtbl_pc;
	PCRawCtor(&this->m_pc);
}

void PCCCtor(pc *this, pc *other)
{
	PTCCtor((pt *)this, (pt *)other);
	this->m_vtbl = other->m_vtbl;
	PCRawCCtor(&this->m_pc, &other->m_pc);
}

void PCDtor(pc *this)
{
	PCRawDtor(&this->m_pc);
	this->m_vtbl = (vtbl_pc *)&g_vtbl_pt;
	PTDtor((pt *)this);
}

void PCDisplay(const pc *this)
{
	this->m_pc.m_pt1->m_vtbl->display(this->m_pc.m_pt1);
	this->m_pc.m_pt2->m_vtbl->display(this->m_pc.m_pt2);

	MBDisplay(&this->m_pc.m_mb);
	TDisplay(&this->m_pc.m_taxi);
}

static void PCRawCtor(pc_raw *this)
{
	pt *temp = (pt *)malloc(sizeof(mb));
	ExitIfBad(NULL != temp);
	MBCtor((mb *)temp);
	this->m_pt1 = temp;

	temp = (pt *)malloc(sizeof(taxi));
	ExitIfBad(NULL != temp);
	TCtor((taxi *)temp);
	this->m_pt2 = temp;

	MBCtor(&this->m_mb);
	TCtor(&this->m_taxi);	
}

static void PCRawCCtor(pc_raw *this, pc_raw *other)
{
	pt *temp = (pt *)malloc(sizeof(mb));
	ExitIfBad(NULL != temp);
	MBCCtor((mb *)temp, (mb *)other->m_pt1);
	this->m_pt1 = temp;

	temp = (pt *)malloc(sizeof(taxi));
	ExitIfBad(NULL != temp);
	TCCtor((taxi *)temp, (taxi *)other->m_pt2);
	this->m_pt2 = temp;

	MBCCtor(&this->m_mb, &other->m_mb);
	TCCtor(&this->m_taxi, &other->m_taxi);	
}

static void PCRawDtor(pc_raw *this)
{
	this->m_pt1->m_vtbl->dtor(this->m_pt1);
	free(this->m_pt1);
	this->m_pt1 = NULL;

	this->m_pt2->m_vtbl->dtor(this->m_pt2);
	free(this->m_pt2);
	this->m_pt2 = NULL;

	TDtor(&this->m_taxi);
	MBDtor(&this->m_mb);
}

/**************************************************************************
Functions 
**************************************************************************/

#define MAX_FUNC(t1, t2) ((t1 > t2) ? (t1) : (t2))

void PIDisplay(const pt *pt)
{
	pt->m_vtbl->display(pt);
}

void PIWash(const mb *mb)
{
	mb->m_vtbl->wash(mb, 3);
}

static pt PIRet(int i)
{
	mb ret1;
	pt ret2;
	MBCtor(&ret1);
	printf("print_info(int i)\n");
	MBDisplay(&ret1);
	PTCCtor(&ret2, (pt *)&ret1);
	MBDtor(&ret1);
	(void)i;
	return ret2;
}

static void TaxiDisplay(taxi t)
{
	taxi t2;
	TCCtor(&t2, &t);
	TDisplay(&t2);
	TDtor(&t2);
}

/**************************************************************************
Main 
**************************************************************************/

int main(void)
{
	int i = 0;
	mb mb1;
	pt pt1;
	pt *array[3];
	pt array2[3];
	mb mb2;
	mb array3[4];
	taxi *array4;
	st st;
	pc *ts1;
	pc *ts2;

	/*********************************************/

	MBCtor(&mb1);
	PIWash(&mb1);

	/*********************************************/

	pt1 = PIRet(3);
	PTDisplay(&pt1);
	PTDtor(&pt1);

	/*********************************************/

	array[0] = (pt *)malloc(sizeof(mb));
	ExitIfBad(NULL != array[0]);;
	MBCtor((mb *)array[0]);

	array[1] = (pt *)malloc(sizeof(taxi));
	ExitIfBad(NULL != array[1]);;
	TCtor((taxi *)array[1]);

	array[2] = (pt *)malloc(sizeof(mb));
	ExitIfBad(NULL != array[2]);;
	MBCtor((mb *)array[2]);

	for (i = 0; i < 3; ++i)
	{
		PIDisplay(array[i]);
	}

	MBDtor((mb *)array[0]);
	TDtor((taxi *)array[1]);
	MBDtor((mb *)array[2]);

	for (i = 0; i < 3; ++i)
	{
		free(array[i]);
		array[i] = NULL;
	}

	/*********************************************/

	{
		mb temp;

		MBCtor(&temp);
		PTCCtor(&array2[0], (pt *)&temp);
		MBDtor(&temp);
	}

	{
		taxi temp;

		TCtor(&temp);
		TDtor(&temp);
	}

		PTCCtor(&array2[1], (pt *)&temp);
	PTCtor(&array2[2]);

	for (i = 0; i < 3; ++i)
	{
		PTDisplay(&array2[i]);
	}

	PTDisplay(&array2[0]);

	/*********************************************/

	PrintCount();		

	/*********************************************/

	MBCtor(&mb2);
	PrintCount();

	/*********************************************/

	for (i = 0; i < 4; ++i)
	{
		MBCtor(&array3[i]);
	}

	/*********************************************/

	array4 = (taxi *)malloc(4 * sizeof(taxi));

	for (i = 0; i < 4; ++i)
	{
		TCtor(&array4[i]);
	}

	for (--i; i >= 0; --i)
	{
		TDtor(&array4[i]);
	}

	free(array4);

	/*********************************************/

	printf("%d\n", MAX_FUNC(1, 2));
	printf("%d\n", (int)MAX_FUNC(1, 2.0));

	/*********************************************/

	STCtor(&st);
	TaxiDisplay(*((taxi*)&st));

	/*********************************************/

	ts1 = (pc *)malloc(sizeof(pc));
	ExitIfBad(NULL != ts1);
	ts2 = (pc *)malloc(sizeof(pc));
	ExitIfBad(NULL != ts2);

	PCCtor(ts1);
	PCCCtor(ts2, ts1);

	PCDisplay(ts1);
	PCDisplay(ts2);

	PCDtor(ts1);
	free(ts1);
	ts1 = NULL;

	PCDisplay(ts2);
	PCDtor(ts2);
	free(ts2);
	ts2 = NULL;

	/*********************************************/

	STDtor(&st);
	for (i = 3; i >= 0; --i)
	{
		MBDtor(&array3[i]);
	}
	MBDtor(&mb2);
	for (i = 2; i >= 0; --i)
	{
		PTDtor(&array2[i]);
	}
	MBDtor(&mb1);

	return 0;
}

