/******************************************************************************
Title: DHCP - Infinity Labs R&D 
Group: Ol91
Description: DHCP interface
******************************************************************************/

#ifndef __DHCP_ILRD_OL91__
#define __DHCP_ILRD_OL91__

#include <stddef.h> /* size_t */

#define IP_SIZE (4)

typedef struct dhcp dhcp_t;
typedef unsigned char ip_t[IP_SIZE];

typedef enum {
	SUCCESS, 
	ALLOCATION_FAILED, 
	NO_ADDRESS_AVAILABLE,
	ADDRESS_UNAVAILABLE, 
	INVALID_SUBNET,
	INVALID_ADDRESS
} status_t;

/*****************************************************************************/
/*
Decription:         Create a new instance of DHCP.
Input:	            Subnet ip for which the DHCP will manage the addresses 
                    Size of the subnet in bits?. Mask should be class A, B or C sized
Output:		        Pointer to the DHCP	
Error proccessing:  NULL if memory allocation failed
Time complexity:    O(1)
*/
dhcp_t *DhcpCreate(ip_t subnet_ip, size_t mask_size);

/*****************************************************************************/
/*
Decription: 	    Destroy the DHCP
Input:			    DHCP
Output:			    none
Error proccessing:  none
Time complexity:    O(n)
*/
void DhcpDestroy(dhcp_t *dhcp);

/*****************************************************************************/
/*
Decription: 	    Generate a unique adress equal or bigger to the prefered ip
                    if the address asked is not available

Input:			    DHCP, prefered ip, out parameter that will contain the 
                    generated ip address
Output:			    SUCCESS if the address was generated
                    UNAVAILABLE_ADDRESS if the ip address asked is not available 
Error proccessing:  DHCP_IS_FULL if no address available
                    INVALID_SUBNET if the address doesn't contain the correct subnet

Time complexity:    O(log(n))
*/
status_t DhcpAllocateIp(dhcp_t *dhcp, ip_t preferred_ip, ip_t _ip_allocated);

/*****************************************************************************/
/*
Decription: 	    Free an ip address from the DHCP

Input:			    DHCP and adress to free
Output:			    SUCCESS if the address was free'd
Error proccessing:  INVALID_ADDRESS if the address is unoccupied or if the address
                    doesn't contain the correct subnet 

Time complexity:    O(log(n))
*/
status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip);

/*****************************************************************************/
/*
Decription: 	    Count the amount of free address in the DHCP
Input:			    DHCP
Output:			    Number of free addresses
Error proccessing:  none
Time complexity:    O(n)
*/
size_t DhcpCountFree(const dhcp_t *dhcp);

#endif /* __DHCP_ILRD_OL91__ */
