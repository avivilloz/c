/****************************************************************************
Title: UID - Infinity Labs R&D 
Group: Ol91
Description: UID
****************************************************************************/

#ifndef __UID_H_ILRD_OL91__
#define __UID_H_ILRD_OL91__

#include <sys/types.h>	/* pid_t */

/*****************************************************************************/

typedef struct uid ilrd_uid_t;

struct uid
{
	time_t time;
	pid_t pid;
	unsigned long counter;
};

/*****************************************************************************/

extern const ilrd_uid_t BAD_UID;

/*****************************************************************************/
/*
Decription:         Create new UID	
Input:              No
Output:             New UID		
Error proccessing:  Returns BAD_UID if the function fails 
*/

ilrd_uid_t UIDCreate(void);

/*****************************************************************************/
/*
Decription:         Compares two UID	
Input:              Two UID 
Output:             1 if UID are the same, 0 if different
Error proccessing:  No
*/ 
           
int UIDIsSame(ilrd_uid_t lhs, ilrd_uid_t rhs);

/*****************************************************************************/

#endif /*__UID_H_ILRD_OL91__*/
