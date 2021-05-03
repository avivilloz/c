/*****************************************************************************
Title: broadcast
Description: broadcast api
******************************************************************************/

#include <stdlib.h> /* atoi */
#include <string.h> /* memset */

#include "broadcast.h" /* api */

#define h_addr h_addr_list[0]

/****************************************************************************/

int BroadcastSetup(
    const char *host_ip, 
    const char *port, 
    struct sockaddr_in *_buff
)
{
	struct hostent *host_entries;

	host_entries = gethostbyname(host_ip);
	PERROR_IF_BAD((NULL == host_entries), "gethostbyname", return -1);

	_buff->sin_family = AF_INET;
	_buff->sin_port = htons(atoi(port));
	_buff->sin_addr = *(struct in_addr *)host_entries->h_addr;
	memset(_buff->sin_zero, '\0', sizeof(_buff->sin_zero));

	return 0;
}

/****************************************************************************/
