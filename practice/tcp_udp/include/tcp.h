/*****************************************************************************
Title: tcp 
Description: tcp api
******************************************************************************/

#ifndef __ILRD_OL91_TCP_H__
#define __ILRD_OL91_TCP_H__

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

#endif /*__ILRD_OL91_TCP_H__*/
