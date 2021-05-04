/*****************************************************************************
Title: Client
Author: Aviv Illoz
Description: Client
******************************************************************************/

#include <unistd.h>          /* pause */

#include "live_or_let_die.h" /* api */

#define TIME_TO_SLEEP 5

/********************************* TESTS *************************************/

static void TestKeepMeAlive(int argc, char *argv[])
{
	size_t i = 0;
	KeepMeAlive(argc, argv);	
	for (; i < TIME_TO_SLEEP; ++i)
	{
		pause();
	}
}

static void TestLetMeDie(int argc, char *argv[])
{
	size_t i = 0;
	KeepMeAlive(argc, argv);
	for (; i < TIME_TO_SLEEP; ++i)
	{
		pause();
	}
	LetMeDie();
	KeepMeAlive(argc, argv);
	for (i = 0; i < TIME_TO_SLEEP; ++i)
	{
		pause();
	}
	LetMeDie();
	KeepMeAlive(argc, argv);
	for (i = 0; i < TIME_TO_SLEEP; ++i)
	{
		pause();
	}
	LetMeDie();
}

/*****************************************************************************/

int main(int argc, char *argv[])
{
/*
	TestLetMeDie(argc, argv);
*/
	TestKeepMeAlive(argc, argv);

	return 0;
}
