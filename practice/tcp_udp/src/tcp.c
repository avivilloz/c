/*****************************************************************************
Title: tcp 
Description: tcp api
******************************************************************************/

#include "tcp.h" /* api */

/****************************************************************************/

int TCPServerSetup(int sockfd, int backlog)
{
	int status = 0;

	status = listen(sockfd, backlog);
	PERROR_IF_BAD((-1 == status), "listen", return -1);

	return 0;
}

int TCPWaitForRequest(int sockfd, sockaddr_t *_addr)
{
	int connected_fd = 0;
	socklen_t addr_len = sizeof(*_addr);

	connected_fd = accept(sockfd, _addr, &addr_len);
	PERROR_IF_BAD((-1 == connected_fd), "accept", return -1);

	return connected_fd;
}

/****************************************************************************/
