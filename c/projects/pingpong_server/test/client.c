/*****************************************************************************
Title: client 
Author: aviv illoz
Description: client program
******************************************************************************/

#include <stdlib.h> /* exit */
#include <unistd.h> /* close, sleep */
#include <string.h> /* strcmp */

#include "shared.h" /* api */
#include "broadcast.h" /* api */

#define TIMES_TO_SEND 7
#define TIME_TO_WAIT 3
#define MAX_BUFF_SIZE 100

/*****************************************************************************/

static void TCPClient(const char *host_ip, const char *port, const char *msg);
static void UDPClient(const char *host_ip, const char *port, const char *msg);
static void UDPBroadcast(const char *host_ip, const char *port, const char *msg);
static void PingPong(int sockfd, sockaddr_t *addr, const char *msg);

/*****************************************************************************/

int main(int argc, char *argv[])
{
	MSG_IF_BAD((5 != argc), 
	"provide type of client, IP address, port and msg to send", return 1);

	if (0 == strcmp(argv[1], "tcp"))
	{
		TCPClient(argv[2], argv[3], argv[4]);
	}
	else if (0 == strcmp(argv[1], "udp"))
	{
		UDPClient(argv[2], argv[3], argv[4]);
	}
	else if (0 == strcmp(argv[1], "broadcast"))
	{
		UDPBroadcast(argv[2], argv[3], argv[4]);
	}
	else
	{
		printf("client: %s protocol not recognized", argv[1]);
	}

	(void)argc;

	return 0;
}

/*****************************************************************************/

static void TCPClient(const char *host_ip, const char *port, const char *msg)
{
	int status = 0;
	int sockfd = 0;
	size_t i = 0;
	sockaddr_t addr; 

	sockfd = GetSocketFd(host_ip, port, SOCK_STREAM, &addr);
	CHECK_IF_BAD((-1 == sockfd), exit(1));

	status = SetOptions(sockfd, SO_REUSEADDR);
	CHECK_IF_BAD((-1 == status), exit(1));

	for (; i < TIMES_TO_SEND; ++i)
	{
		PingPong(sockfd, NULL, msg);
		sleep(TIME_TO_WAIT);
	}

	PERROR_IF_BAD((-1 == close(sockfd)), "close", exit(1));
}

static void UDPClient(const char *host_ip, const char *port, const char *msg)
{
	int status = 0;
	int sockfd = 0;
	size_t i = 0;
	sockaddr_t addr; 

	sockfd = GetSocketFd(host_ip, port, SOCK_DGRAM, &addr);
	CHECK_IF_BAD((-1 == sockfd), exit(1));

	status = SetOptions(sockfd, SO_REUSEADDR);
	CHECK_IF_BAD((-1 == status), exit(1));

	for (; i < TIMES_TO_SEND; ++i)
	{
		PingPong(sockfd, &addr, msg);
		sleep(TIME_TO_WAIT);
	}	

	PERROR_IF_BAD((-1 == close(sockfd)), "close", exit(1));
}

static void UDPBroadcast(const char *host_ip, const char *port, const char *msg)
{
	int sockfd = 0;
	int status = 0;
	struct sockaddr_in addr;

	sockfd = GetSocketFd(host_ip, port, SOCK_DGRAM, NULL);
	CHECK_IF_BAD((-1 == sockfd), exit(1));

	status = SetOptions(sockfd, SO_BROADCAST);
	CHECK_IF_BAD((-1 == status), exit(1));

	status = BroadcastSetup(host_ip, port, &addr);
	CHECK_IF_BAD((-1 == status), exit(1));

	PingPong(sockfd, (sockaddr_t *)&addr, msg);

	PERROR_IF_BAD((-1 == close(sockfd)), "close", exit(1));
}

static void PingPong(int sockfd, sockaddr_t *addr, const char *msg)
{
	int status = 0;
	char buff[MAX_BUFF_SIZE];
	socklen_t addr_len = sizeof(*addr);

	status = sendto(sockfd, msg, strlen(msg) + 1, 0, addr, addr_len);
	PERROR_IF_BAD((-1 == status), "sendto", exit(1));

	if (0 != strcmp(msg, "ping"))
	{
		exit(0);
	}

	status = recvfrom(sockfd, buff, MAX_BUFF_SIZE - 1, 0, addr, &addr_len);
	PERROR_IF_BAD((-1 == status), "recvfrom", exit(1));

	printf("%s\n", buff);
}

/*****************************************************************************/
