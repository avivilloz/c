/*****************************************************************************
Title: tcp 
Author: aviv illoz
Description: tcp api
******************************************************************************/

#ifndef __TCP_H__
#define __TCP_H__

#include "shared.h" /* macros and typedefs */

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
*/

int TCPServerSetup(int sockfd, int backlog);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
*/

int TCPWaitForRequest(int sockfd, sockaddr_t *_addr);

/*****************************************************************************/

#endif /*__TCP_H__*/
