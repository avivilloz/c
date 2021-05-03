/*****************************************************************************
Title: ext2 - Infinity Labs R&D 
Group: OL91
Author: Aviv
Description: ext2 test
******************************************************************************/

#include <stdio.h> /* printf */

#include "ext2.h" /* api */

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		fputs("error: device name or path to file not provided\n", stderr);
		return 1;
	}

	PrintFileInfo(argv[1], argv[2]);

	(void)argc;

	return 0;
}

/*****************************************************************************/

