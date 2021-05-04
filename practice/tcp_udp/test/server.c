/*****************************************************************************
Title: server 
Author: aviv illoz
Description: server program 
******************************************************************************/

#include <stdlib.h> /* exit */
#include <unistd.h> /* close */

#include "shared.h" /* api */
#include "tcp.h" /* api */

#define MAX_BUFF_SIZE 100
#define BACKLOG 10
#define CHILD 0

/*****************************************************************************/

static int TCPServer(const char *port, const char *msg)
{
	int status = 0;
	int sockfd = 0;
	sockaddr_t addr;

	sockfd = GetSocketFd(NULL, port, SOCK_STREAM, &addr);
	CHECK_IF_BAD((-1 == sockfd), return 1);

	status = SetOptions(sockfd, SO_REUSEADDR);
	CHECK_IF_BAD((-1 == status), return 1);

	status = TCPServerSetup(sockfd, BACKLOG);
	CHECK_IF_BAD((-1 == status), return 1);

	while (1)
	{
		int pid = 0;
		int connected_fd = 0;
		char buff[MAX_BUFF_SIZE];

		connected_fd = TCPWaitForRequest(sockfd, &addr);
		CHECK_IF_BAD((-1 == connected_fd), return 1);

		PrintAddr(addr.sa_family, &addr);

		pid = fork();
		PERROR_IF_BAD((-1 == pid), "fork", return 1);

		if (CHILD == pid)
		{
			PERROR_IF_BAD((-1 == close(sockfd)), "close", exit(1));

			while (1)
			{
				status = ReceiveMsg(connected_fd, buff, MAX_BUFF_SIZE, NULL);
				CHECK_IF_BAD((-1 == status), exit(1));

				printf("%s\n", buff);

				status = SendMsg(connected_fd, msg, NULL);
				CHECK_IF_BAD((-1 == status), exit(1));
			}

			PERROR_IF_BAD((-1 == close(connected_fd)), "close", exit(1)); /* not relevant */

			exit(0);
		}

		PERROR_IF_BAD((-1 == close(connected_fd)), "close", return 1);
	}

	PERROR_IF_BAD((-1 == close(sockfd)), "close", return 1); /* not relevant */

	return 0;
}

static int UDPServer(const char *port, const char *msg)
{
	int status = 0;
	int sockfd = 0;
	sockaddr_t addr;

	sockfd = GetSocketFd(NULL, port, SOCK_DGRAM, &addr);
	CHECK_IF_BAD((-1 == sockfd), return 1);

	status = SetOptions(sockfd, SO_REUSEADDR);
	CHECK_IF_BAD((-1 == status), return 1);

	while (1)
	{
		char buff[MAX_BUFF_SIZE];
	
		status = ReceiveMsg(sockfd, buff, MAX_BUFF_SIZE, &addr);
		CHECK_IF_BAD((-1 == status), return 1);

		PrintAddr(addr.sa_family, &addr);
		
		printf("%s\n", buff);

		status = SendMsg(sockfd, msg, &addr);
		CHECK_IF_BAD((-1 == status), return 1);
	}

	PERROR_IF_BAD((-1 == close(sockfd)), "close", return 1); /* not relevant */

	return 0;
}

int main(int argc, char *argv[])
{
	CHECK_IF_BAD((1 == TCPServer(argv[1], argv[2])), return 1);
	/*
	CHECK_IF_BAD((1 == UDPServer(argv[1], argv[2])), return 1);
	*/

	(void)argc;

	return 0;
}

/*****************************************************************************/

