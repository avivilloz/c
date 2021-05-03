/*****************************************************************************
Title: broadcast
Description: broadcast api
******************************************************************************/

#ifndef __ILRD_OL91_BROADCAST_H__
#define __ILRD_OL91_BROADCAST_H__

#include "shared.h" /* macros and typedefs */

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
*/

int BroadcastSetup(
    const char *host_ip, 
    const char *port, 
    struct sockaddr_in *_buff
);

/*****************************************************************************/

#endif /*__ILRD_OL91_BROADCAST_H__*/
