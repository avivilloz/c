/****************************************************************************
Title: menu
Author: Aviv
Description: menu interface
*****************************************************************************/

#ifndef _MENU_H_
#define _MENU_H_

enum status {CONTINUE, EXIT};

typedef struct operations
{
	unsigned int cmd;
	int (*cmp)(unsigned int cmd, unsigned int key);
	int (*action)(void);
	char *name;
} op_t;

/*****************************************************************************/

int Logger(op_t array[], size_t size);

/*****************************************************************************/

int AnalizeCmds(unsigned int key, op_t array[], size_t size);

/*****************************************************************************/

int Return(void);

/*****************************************************************************/

#endif /*_MENU_H_*/
