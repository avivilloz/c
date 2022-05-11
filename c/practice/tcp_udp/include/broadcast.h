/*****************************************************************************
Title: broadcast
Author: aviv illoz
Description: broadcast api
******************************************************************************/

#ifndef __BROADCAST_H__
#define __BROADCAST_H__

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

#endif /*__BROADCAST_H__*/
