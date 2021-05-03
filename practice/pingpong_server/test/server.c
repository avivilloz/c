/*****************************************************************************
Title: server 
Description: server program 
******************************************************************************/

#include <stdlib.h> /* exit */
#include <unistd.h> /* close */
#include <sys/time.h> /* timeval */
#include <string.h> /* strcmp */
#include <fcntl.h> /* fcntl */

#include "shared.h" /* api */

#define MAX_BUFF_SIZE 100
#define BACKLOG 10
#define TIMEOUT 7

typedef void (*fd_handler)(int);

static fd_handler g_fd_handlers[FD_SETSIZE];
static fd_set g_master_readset; 

/*****************************************************************************/

static void Server(const char *port);
static void PrepareSocketsAndHandlers(const char *port);
static void PrepareSocket(const char *port, int socktype, fd_handler handler);
static int WaitForInput(fd_set *readset);
static void StdinHandler(int sockfd);
static void TCPAccept(int sockfd);
static void PingPong(int sockfd);

/*****************************************************************************/

int main(int argc, char *argv[])
{
	MSG_IF_BAD((2 != argc), "provide port", return 1);

	Server(argv[1]);

	(void)argc;

	return 0;
}

/*****************************************************************************/

static void Server(const char *port)
{
	int status = 0;
	size_t i = 0;
	fd_set readset;

	PrepareSocketsAndHandlers(port);

	while (1)
	{
		readset = g_master_readset;
		status = WaitForInput(&readset);
		CHECK_IF_BAD((1 == status), continue);	

		for (i = 0; i < FD_SETSIZE; ++i)
		{
			if (FD_ISSET(i, &readset))
			{
				g_fd_handlers[i](i);
			}
		}
	}
}

static void PrepareSocketsAndHandlers(const char *port)
{
	g_fd_handlers[STDIN_FILENO] = StdinHandler;
	FD_SET(STDIN_FILENO, &g_master_readset);

	PrepareSocket(port, SOCK_STREAM, TCPAccept);
	PrepareSocket(port, SOCK_DGRAM, PingPong);
}

static void PrepareSocket(const char *port, int socktype, fd_handler handler)
{
	int status = 0;
	int sockfd = 0;

	sockfd = GetSocketFd(NULL, port, socktype, NULL);
	CHECK_IF_BAD((-1 == sockfd), exit(1));

	status = SetOptions(sockfd, SO_REUSEADDR);
	CHECK_IF_BAD((-1 == status), exit(1));

	status = fcntl(sockfd, F_SETFL, O_NONBLOCK);
	PERROR_IF_BAD((-1 == status), "fcntl", exit(1));

	if (SOCK_STREAM == socktype)
	{
		status = listen(sockfd, BACKLOG);
		PERROR_IF_BAD((-1 == status), "listen", exit(1));
	}

	g_fd_handlers[sockfd] = handler;
	FD_SET(sockfd, &g_master_readset);
}

static int WaitForInput(fd_set *readset)
{
	int status = 0;
	struct timeval timeout = {TIMEOUT, 0};

	status = select(FD_SETSIZE, readset, NULL, NULL, &timeout);
	PERROR_IF_BAD((-1 == status), "select", exit(1));	
	MSG_IF_BAD((0 == status), "select: time's out", return 1);	

	return 0;
}

static void StdinHandler(int sockfd)
{
	int numbytes = 0;
	char buff[MAX_BUFF_SIZE];

	numbytes = read(sockfd, buff, MAX_BUFF_SIZE);
	PERROR_IF_BAD((-1 == numbytes), "read", exit(1));
	buff[numbytes - 1] = '\0';

	if (0 == strcmp(buff, "ping"))
	{
		puts("pong");
	}
	else if (0 == strcmp(buff, "quit"))
	{
		exit(0);
	}
}

static void TCPAccept(int sockfd)
{
	int status = 0;
	int new_sockfd = 0;

	new_sockfd = accept(sockfd, NULL, NULL);
	PERROR_IF_BAD((-1 == new_sockfd), "accept", exit(1));

	status = fcntl(new_sockfd, F_SETFL, O_NONBLOCK);
	PERROR_IF_BAD((-1 == status), "fcntl", exit(1));

	g_fd_handlers[new_sockfd] = PingPong;
	FD_SET(new_sockfd, &g_master_readset);
}

static void PingPong(int sockfd)
{
	int status = 0;
	sockaddr_t addr;
	socklen_t addr_len = sizeof(addr);
	char buff[MAX_BUFF_SIZE];

	status = recvfrom(sockfd, buff, MAX_BUFF_SIZE - 1, 0, &addr, &addr_len);
	PERROR_IF_BAD((-1 == status), "recvfrom", exit(1));
	if (0 == status)
	{
		FD_CLR(sockfd, &g_master_readset);
		PERROR_IF_BAD((-1 == close(sockfd)), "close", exit(1));
		puts("recvfrom: fd closed");
		return;
	}

	printf("%s\n", buff);

	if (0 == strcmp(buff, "ping"))
	{
		status = sendto(sockfd, "pong", strlen("pong") + 1, 0, &addr, addr_len);
		PERROR_IF_BAD((-1 == status), "sendto", exit(1));
	}
}

/*****************************************************************************/
