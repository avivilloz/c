/****************************************************************************
Title: Menu	
Author: Aviv Illoz
Description: Menu 
*****************************************************************************/

#include <stdio.h>	/* printf */

#include "menu.h"	/* api */

/*****************************************************************************/

int Logger(op_t array[], size_t size)
{
	unsigned int key = 0;
	int check = 0;	
	size_t i = 0;

	do {
		printf("\nOptions:\n");
		for (i = 0; i < size; ++i)
		{
			printf("%u-%s  ", array[i].cmd, array[i].name);
		}
		printf("\n");
		scanf("%u", &key);
		check = AnalizeCmds(key, array, size);	
	} while (EXIT != check);

	return check;
}

/*****************************************************************************/

int AnalizeCmds(unsigned int key, op_t array[], size_t size)
{
	int check = 0;
	size_t i = 0;	

	for (; i < size; ++i)
	{
		if (array[i].cmp(key, array[i].cmd))
		{
			getchar();
			check = array[i].action();
		}
	}

	return check;
}

/*****************************************************************************/

int Return(void)
{
	return EXIT;
}
