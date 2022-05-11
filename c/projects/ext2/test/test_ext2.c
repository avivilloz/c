/*****************************************************************************
Title: ext2
Author: Aviv Illoz
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
