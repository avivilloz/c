/*****************************************************************************
Title: shared
Description: shared api
******************************************************************************/

#ifndef __ILRD_OL91_SHARED_H__
#define __ILRD_OL91_SHARED_H__

#include <stdio.h> /* perror */
#include <netdb.h> /* addrinfo and sockaddr structs */

/*****************************************************************************/

#define PERROR_IF_BAD(is_bad, msg, action) \
    if (1 == is_bad) {perror(msg); action;}

#define MSG_IF_BAD(is_bad, msg, action) \
    if (1 == is_bad) {fputs(msg, stderr); action;}

#define CHECK_IF_BAD(is_bad, action) \
    if (1 == is_bad) {action;}

typedef struct addrinfo addrinfo_t;
typedef struct sockaddr sockaddr_t;

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
*/

int GetSocketFd(
    const char *host, 
    const char *service, 
    int socktype, 
    sockaddr_t *_buff
);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
*/

int SetOptions(int sockfd, int optname);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
*/

void PrintAddr(int family, const sockaddr_t *addr);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
*/

int SendMsg(int sockfd, const char *msg, const sockaddr_t *addr);

/*****************************************************************************/
/*
Decription:	
Input:
Output:
Error:
*/

int ReceiveMsg(int sockfd, char _buff[], size_t buff_size, sockaddr_t *_addr);

/*****************************************************************************/

#endif /*__ILRD_OL91_SHARED_H__*/

