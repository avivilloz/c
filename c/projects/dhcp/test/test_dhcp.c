/*****************************************************************************
Title: DHCP
Author: Aviv Illoz
Description: DHCP Test API
******************************************************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc */
#include <string.h>	/* memcpy */

#include "dhcp.h"	/* api */

#define expect(x)	if (!(x))\
					{\
						return TEST_FAIL;\
					}\

#define RUN_TEST(x)	if (TEST_FAIL == (x))\
					{\
						printf("%s: \33[5;1;31mFAILURE\33[0m\n", #x);\
						success = FALSE;\
					}\
					else\
					{\
						printf("%s: \33[5;1;32;1mSUCCESS\33[0m\n", #x);\
					}

/*****************************************************************************/

enum {FALSE, TRUE};
typedef enum {TEST_PASS, TEST_FAIL} test_status_t;

/********************************* TESTS *************************************/

static test_status_t DhcpCreateDestroyTest(void)
{
	ip_t subnet_ip = {'a','b',0,0};
	dhcp_t *dhcp = DhcpCreate(subnet_ip, 16);
	if (NULL == dhcp)
	{
		return TEST_FAIL;
	}

	DhcpDestroy(dhcp);

	return TEST_PASS;
}

/*****************************************************************************/

#define IP_LIST_SIZE 65530

static ip_t ip_list[IP_LIST_SIZE];

static void InitList(ip_t *ip_list)
{
	size_t i = 0;
	ip_t ip = {97, 98, 0,0};

	for (; i < IP_LIST_SIZE; ++i)
	{
		memcpy(ip_list[i], ip, IP_SIZE);
	}
}

static void PrintIp(ip_t ip)
{
	size_t i = 0;
	
	for (; i < IP_SIZE; ++i)
	{
		printf("%d ", ip[i]);
	}
	printf("\n");
}

static test_status_t DhcpAllocateIpTest(void)
{
	ip_t subnet_ip = {97, 98, 0, 0};
	ip_t recipient = {97, 98, 0, 0};
	ip_t invalid_subnet = {54, 32, 0 ,0};
	ip_t preferred_ip = {97, 98, 44, 35};
	ip_t last_ip_available = {97, 98, 255, 253};
	size_t i = 0;
	dhcp_t *dhcp = DhcpCreate(subnet_ip, 16);
	if (NULL == dhcp)
	{
		return TEST_FAIL;
	}

	expect(INVALID_SUBNET == DhcpAllocateIp(dhcp, invalid_subnet, recipient));

	expect(SUCCESS == DhcpAllocateIp(dhcp, preferred_ip, recipient));
	/*PrintIp(recipient);*/

	expect(SUCCESS == DhcpAllocateIp(dhcp, last_ip_available, recipient));
	/*PrintIp(recipient);*/
	expect(ADDRESS_UNAVAILABLE == DhcpAllocateIp(dhcp, last_ip_available, recipient));
	/*PrintIp(recipient);*/

	InitList(ip_list);

	for (; i < IP_LIST_SIZE; ++i)
	{
		expect(ADDRESS_UNAVAILABLE == DhcpAllocateIp(dhcp, subnet_ip, ip_list[i]));
		/*PrintIp(ip_list[i]);*/
	}

	expect(NO_ADDRESS_AVAILABLE == DhcpAllocateIp(dhcp, subnet_ip, recipient));
/*
*/
	DhcpDestroy(dhcp);

	return TEST_PASS;
}

/*****************************************************************************/

static test_status_t DhcpFreeIpTest(void)
{
	ip_t subnet_ip = {97, 98, 0, 0};
	ip_t broadcast = {97, 98, 255, 255};
	ip_t server = {97, 98, 255, 254};
	size_t i = 0;
	dhcp_t *dhcp = DhcpCreate(subnet_ip, 16);
	if (NULL == dhcp)
	{
		return TEST_FAIL;
	}
	
	expect(INVALID_ADDRESS == DhcpFreeIp(dhcp, subnet_ip)); /* network */
	expect(INVALID_ADDRESS == DhcpFreeIp(dhcp, broadcast));
	expect(INVALID_ADDRESS == DhcpFreeIp(dhcp, server));

/*
	InitList(ip_list);
*/
	for (; i < IP_LIST_SIZE; ++i)
	{
		expect(ADDRESS_UNAVAILABLE == DhcpAllocateIp(dhcp, subnet_ip, ip_list[i]));
	}

	for (i = 0; i < IP_LIST_SIZE; ++i)
	{
		expect(SUCCESS == DhcpFreeIp(dhcp, ip_list[i]));
		expect(INVALID_ADDRESS == DhcpFreeIp(dhcp, ip_list[i]));
	}
	
	DhcpDestroy(dhcp);

	return TEST_PASS;
}

/*****************************************************************************/

static test_status_t DhcpCountFreeTest(void)
{
	ip_t subnet_ip = {97, 98, 0, 0};
	ip_t recipient1 = {97, 98, 0, 0};
	ip_t recipient2 = {97, 98, 0, 0};
	ip_t recipient3 = {97, 98, 0, 0};
	size_t i = 0;
	dhcp_t *dhcp = DhcpCreate(subnet_ip, 16);
	if (NULL == dhcp)
	{
		return TEST_FAIL;
	}

	expect(65533 == DhcpCountFree(dhcp));
	expect(ADDRESS_UNAVAILABLE == DhcpAllocateIp(dhcp, subnet_ip, recipient1));
	expect(65532 == DhcpCountFree(dhcp));
	expect(ADDRESS_UNAVAILABLE == DhcpAllocateIp(dhcp, subnet_ip, recipient2));
	expect(65531 == DhcpCountFree(dhcp));
	expect(ADDRESS_UNAVAILABLE== DhcpAllocateIp(dhcp, subnet_ip, recipient3));
	expect(65530 == DhcpCountFree(dhcp));
/*
	InitList(ip_list);
*/
	for (; i < IP_LIST_SIZE; ++i)
	{
		expect(ADDRESS_UNAVAILABLE == DhcpAllocateIp(dhcp, subnet_ip, ip_list[i]));
	}

	for (i = 0; i < IP_LIST_SIZE; ++i)
	{
		expect(i == DhcpCountFree(dhcp));
		expect(SUCCESS == DhcpFreeIp(dhcp, ip_list[i]));
		printf("%ld\n", i);
	}

	expect(65530 == DhcpCountFree(dhcp));
	expect(SUCCESS == DhcpFreeIp(dhcp, recipient3));
	expect(65531 == DhcpCountFree(dhcp));
	expect(SUCCESS == DhcpFreeIp(dhcp, recipient2));
	expect(65532 == DhcpCountFree(dhcp));
	expect(SUCCESS == DhcpFreeIp(dhcp, recipient1));
	expect(65533 == DhcpCountFree(dhcp));
	
	DhcpDestroy(dhcp);

	return TEST_PASS;
}

/*****************************************************************************/

int main(void)
{
	int success = TRUE;
/*
*/
	RUN_TEST(DhcpCreateDestroyTest());
	RUN_TEST(DhcpAllocateIpTest());
	RUN_TEST(DhcpFreeIpTest());
	RUN_TEST(DhcpCountFreeTest());	
/*
*/

	if (success)
	{
		printf("Test was a: \33[5;1;32;1mSUCCESS\33[0m\n");
	}
	else
	{
		printf("Test was a: \33[5;1;31mFAILURE\33[0m\n");
	}

	return 0;
}
