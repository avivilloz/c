/*****************************************************************************
Title: client 
Author: aviv illoz
Description: client program
******************************************************************************/

#include <unistd.h> /* close */

#include "shared.h" /* api */
#include "broadcast.h" /* api */

#define MAX_BUFF_SIZE 100

/*****************************************************************************/

static int TCPClient(const char *host_ip, const char *port, const char *msg)
{
	int status = 0;
	int sockfd = 0;
	sockaddr_t addr; 
	char buff[MAX_BUFF_SIZE];

	sockfd = GetSocketFd(host_ip, port, SOCK_STREAM, &addr);
	CHECK_IF_BAD((-1 == sockfd), return 1);

	status = SetOptions(sockfd, SO_REUSEADDR);
	CHECK_IF_BAD((-1 == status), return 1);

	PrintAddr(addr.sa_family, &addr);

	while (1)
	{
		status = SendMsg(sockfd, msg, NULL);
		CHECK_IF_BAD((-1 == status), return 1);

		status = ReceiveMsg(sockfd, buff, MAX_BUFF_SIZE, NULL);
		CHECK_IF_BAD((-1 == status), return 1);

		printf("%s\n", buff);
	}

	PERROR_IF_BAD((-1 == close(sockfd)), "close", return 1); /* not relevant */

	return 0;
}

static int UDPClient(const char *host_ip, const char *port, const char *msg)
{
	int status = 0;
	int sockfd = 0;
	sockaddr_t addr; 

	sockfd = GetSocketFd(host_ip, port, SOCK_DGRAM, &addr);
	CHECK_IF_BAD((-1 == sockfd), return 1);

	status = SetOptions(sockfd, SO_REUSEADDR);
	CHECK_IF_BAD((-1 == status), return 1);

	PrintAddr(addr.sa_family, &addr);

	while (1)
	{
		char buff[MAX_BUFF_SIZE];

		status = SendMsg(sockfd, msg, &addr);
		CHECK_IF_BAD((-1 == status), return 1);

		status = ReceiveMsg(sockfd, buff, MAX_BUFF_SIZE, &addr);
		CHECK_IF_BAD((-1 == status), return 1);

		PrintAddr(addr.sa_family, &addr);

		printf("%s\n", buff);
	}	

	PERROR_IF_BAD((-1 == close(sockfd)), "close", return 1); /* not relevant */

	return 0;
}

static int UDPBroadcast(const char *host_ip, const char *port, const char *msg)
{
	int sockfd = 0;
	int status = 0;
	struct sockaddr_in their_addr;

	sockfd = GetSocketFd(host_ip, port, SOCK_DGRAM, NULL);
	CHECK_IF_BAD((-1 == sockfd), return 1);

	status = SetOptions(sockfd, SO_BROADCAST);
	CHECK_IF_BAD((-1 == status), return 1);

	status = BroadcastSetup(host_ip, port, &their_addr);
	CHECK_IF_BAD((-1 == status), return 1);

	status = SendMsg(sockfd, msg, (sockaddr_t *)&their_addr);
	CHECK_IF_BAD((-1 == status), return 1);

	PERROR_IF_BAD((-1 == close(sockfd)), "close", return 1);

	return 0;
}

int main(int argc, char *argv[])
{
	CHECK_IF_BAD((1 == TCPClient(argv[1], argv[2], argv[3])), return 1);
	/*
	CHECK_IF_BAD((1 == UDPBroadcast(argv[1], argv[2], argv[3])), return 1);
	CHECK_IF_BAD((1 == UDPClient(argv[1], argv[2], argv[3])), return 1);
	*/

	(void)argc;

	return 0;
}

/*****************************************************************************/

