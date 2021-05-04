/*****************************************************************************
Title: DHCP
Author: Aviv Illoz
Description: DHCP API
******************************************************************************/

#include <stdlib.h>		/* malloc, free */
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */
#include <limits.h>		/* CHAR_BIT */

#include "dhcp.h"		/* api */

/*****************************************************************************/

#define BITS_SIZE (IP_SIZE * CHAR_BIT)

enum {OFF, ON, NUM_OF_BITS};

/*****************************************************************************/

typedef struct dhcp_node dhcp_node_t;

struct dhcp
{
	ip_t subnet_ip;
	size_t mask_size;
	dhcp_node_t *root;
};

struct dhcp_node
{
	dhcp_node_t *children[NUM_OF_BITS];
	int is_full;
};

/**************************** STATIC FUNCTIONS *******************************/

static status_t CreateNetwork(dhcp_t *dhcp);
static status_t CreateBroadcast(dhcp_t *dhcp);
static status_t CreateServerAddress(dhcp_t *dhcp);

/***********************************/

static void DestroyNodes(dhcp_node_t *node);

/***********************************/

static status_t AllocateIp(
	dhcp_node_t *node,
	ip_t _ip,
	size_t level
);

/***********************************/

static status_t FreeIp(
	dhcp_node_t *node,
	ip_t _ip,
	size_t level
);

/***********************************/

static size_t Count(dhcp_node_t *node, size_t level);

/******************************** HELPER *************************************/

static dhcp_node_t *CreateNode(void)
{
	dhcp_node_t *node = (dhcp_node_t *)malloc(sizeof(dhcp_node_t));
	if (NULL == node)
	{
		return NULL;
	}

	node->children[OFF] = NULL;
	node->children[ON] = NULL;
	node->is_full = 0;

	return node;
}

static size_t GetMaskInBytes(dhcp_t *dhcp)
{
	return dhcp->mask_size / CHAR_BIT;
}

static size_t GetBitsAvailable(dhcp_t *dhcp)
{
	return BITS_SIZE - dhcp->mask_size;
}

static void GetNetwork(dhcp_t *dhcp, ip_t network)
{
	size_t mask_in_bytes = GetMaskInBytes(dhcp);
	size_t i = 0;

	memcpy(network, dhcp->subnet_ip, mask_in_bytes);
	for (i = mask_in_bytes; i < IP_SIZE; ++i)
	{
		network[i] = 0;
	}
}

static void GetBroadcast(dhcp_t *dhcp, ip_t broadcast)
{
	size_t mask_in_bytes = GetMaskInBytes(dhcp);
	size_t i = 0;

	memcpy(broadcast, dhcp->subnet_ip, mask_in_bytes);
	for (i = mask_in_bytes; i < IP_SIZE; ++i)
	{
		broadcast[i] = 255;
	}
}

static void GetServerAddress(dhcp_t *dhcp, ip_t server)
{
	size_t mask_in_bytes = GetMaskInBytes(dhcp);
	size_t i = 0;

	memcpy(server, dhcp->subnet_ip, mask_in_bytes);
	for (i = mask_in_bytes; i < IP_SIZE - 1; ++i)
	{
		server[i] = 255;
	}
	server[i] = 254;
}

static int IsFull(dhcp_node_t *node)
{
	return node->is_full;
}

static size_t GetBytes(size_t level)
{
	return (level / CHAR_BIT) + (0 != level % CHAR_BIT) + (0 == level);
}

static size_t GetOffset(size_t level)
{
	return CHAR_BIT - (CHAR_BIT * GetBytes(level) - level) - 1;
}

static size_t GetIndex(size_t level)
{
	return IP_SIZE - GetBytes(level);
}

static size_t GetBit(ip_t _ip, size_t index, size_t level)
{
	return 1 & (_ip[index] >> GetOffset(level));
}

static int HasBothChildren(dhcp_node_t *node)
{
	return (NULL != node->children[ON] && NULL != node->children[OFF]);
}

static void UpdateIsFull(dhcp_node_t *node)
{
	if (HasBothChildren(node))
	{
		node->is_full = (IsFull(node->children[ON]) && 
                         IsFull(node->children[OFF]));
	}
}

static void UpdatePreferredIp(ip_t _ip, size_t index, size_t level)
{
	size_t next_index = index + 1;

	for (; next_index < IP_SIZE; ++next_index)
	{
		_ip[next_index] = 0;
	}

	_ip[index] |= 1 << GetOffset(level);
	_ip[index] &= 0xFFFFFFFF << GetOffset(level);
}

static int IsInvalidSubnet(dhcp_t *dhcp, ip_t preferred_ip)
{
	size_t i = 0;
	size_t mask_in_bytes = GetMaskInBytes(dhcp);

	for (; i < mask_in_bytes; ++i)
	{
		if (dhcp->subnet_ip[i] != preferred_ip[i])
		{
			return 1;
		}
	}

	return 0;
}

static status_t GetCorrectStatus(ip_t preferred_ip, ip_t ip_allocated)
{
	size_t i = 0;

	for (; i < IP_SIZE; ++i)
	{
		if (preferred_ip[i] != ip_allocated[i])
		{
			return ADDRESS_UNAVAILABLE; 
		}
	}

	return SUCCESS;
}

static int IsInvalidAddress(dhcp_t *dhcp, ip_t ip)
{
	size_t i = 0;
	ip_t recipient;
	
	GetNetwork(dhcp, recipient);
	for (; i < IP_SIZE && ip[i] == recipient[i]; ++i)
	{}
	if (i == IP_SIZE)
	{
		return 1;
	}

	GetBroadcast(dhcp, recipient);
	for (i = 0; i < IP_SIZE && ip[i] == recipient[i]; ++i)
	{}
	if (i == IP_SIZE)
	{
		return 1;
	}

	GetServerAddress(dhcp, recipient);
	for (i = 0; i < IP_SIZE && ip[i] == recipient[i]; ++i)
	{}
	if (i == IP_SIZE)
	{
		return 1;
	}

	return 0;
}

/******************************* FUNCTIONS ***********************************/

dhcp_t *DhcpCreate(ip_t subnet_ip, size_t mask_size)
{
	dhcp_t *dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if (NULL == dhcp)
	{
		return NULL;
	}

	memcpy(dhcp->subnet_ip, subnet_ip, IP_SIZE);
	dhcp->mask_size = mask_size;

	dhcp->root = CreateNode();
	if (NULL == dhcp->root)
	{
		free(dhcp);
		dhcp = NULL;
		return NULL;
	}

	if (ALLOCATION_FAILED == CreateNetwork(dhcp))
	{
		DhcpDestroy(dhcp);
		return NULL;
	}

	if (ALLOCATION_FAILED == CreateBroadcast(dhcp))
	{
		DhcpDestroy(dhcp);
		return NULL;
	}

	if (ALLOCATION_FAILED == CreateServerAddress(dhcp))
	{
		DhcpDestroy(dhcp);
		return NULL;
	}

	return dhcp;
}

static status_t CreateNetwork(dhcp_t *dhcp)
{
	size_t bits_available = GetBitsAvailable(dhcp);
	ip_t network;

	GetNetwork(dhcp, network);

	return AllocateIp(dhcp->root, network, bits_available);
}

static status_t CreateBroadcast(dhcp_t *dhcp)
{
	size_t bits_available = GetBitsAvailable(dhcp);
	ip_t broadcast;

	GetBroadcast(dhcp, broadcast);

	return AllocateIp(dhcp->root, broadcast, bits_available); 
}

static status_t CreateServerAddress(dhcp_t *dhcp)
{
	size_t bits_available = GetBitsAvailable(dhcp);
	ip_t server;

	GetServerAddress(dhcp, server);

	return AllocateIp(dhcp->root, server, bits_available);
}

/*****************************************************************************/

void DhcpDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	DestroyNodes(dhcp->root);

	free(dhcp);
	dhcp = NULL;
}

static void DestroyNodes(dhcp_node_t *node)
{
	if (NULL != node)
	{
		DestroyNodes(node->children[OFF]);
		DestroyNodes(node->children[ON]);

		free(node);
		node = NULL;
	}
}

/*****************************************************************************/

status_t DhcpAllocateIp(dhcp_t *dhcp, ip_t preferred_ip, ip_t _ip_allocated)
{	
	size_t bits_available = 0;
	int check = SUCCESS;

	assert(NULL != dhcp);

	if (IsInvalidSubnet(dhcp, preferred_ip))
	{
		return INVALID_SUBNET;
	}

	if (IsFull(dhcp->root))
	{
		return NO_ADDRESS_AVAILABLE;
	}

	bits_available = GetBitsAvailable(dhcp);
	memcpy(_ip_allocated, preferred_ip, IP_SIZE);
	check = AllocateIp(dhcp->root, _ip_allocated, bits_available);

	if (ADDRESS_UNAVAILABLE == check)
	{
		GetNetwork(dhcp, _ip_allocated);
		check = AllocateIp(dhcp->root, _ip_allocated, bits_available);
	}

	if (SUCCESS == check)
	{
		check = GetCorrectStatus(preferred_ip, _ip_allocated);
	}

	return check;
}

static status_t AllocateIp(
	dhcp_node_t *node,
	ip_t _ip,
	size_t level
)
{
	if (level > 0)
	{
		size_t index = GetIndex(level);
		size_t preferred_bit = GetBit(_ip, index, level);
		int check = ADDRESS_UNAVAILABLE;

		if (NULL == node->children[preferred_bit])
		{
			node->children[preferred_bit] = CreateNode();
			if (NULL == node->children[preferred_bit])
			{
				return ALLOCATION_FAILED;
			}
		}

		if (!IsFull(node->children[preferred_bit]))
		{
			check = AllocateIp(node->children[preferred_bit], _ip, level - 1);
		}

		if (ADDRESS_UNAVAILABLE == check)
		{
			if (0 == preferred_bit)
			{
				UpdatePreferredIp(_ip, index, level);
				check = AllocateIp(node, _ip, level);
			}
			else
			{
				return ADDRESS_UNAVAILABLE;	
			}
		}

		UpdateIsFull(node);
		
		return check;
	}

	node->is_full = 1;

	return SUCCESS;
}

/*****************************************************************************/

status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip)
{
	size_t bits_available = 0;

	assert(NULL != dhcp);

	if (IsInvalidSubnet(dhcp, ip))
	{
		return INVALID_SUBNET;
	}

	if (IsInvalidAddress(dhcp, ip))
	{
		return INVALID_ADDRESS;
	}

	bits_available = GetBitsAvailable(dhcp);

	return FreeIp(dhcp->root, ip, bits_available);
}

static status_t FreeIp(
	dhcp_node_t *node,
	ip_t ip,
	size_t level
)
{
	if (level > 0)
	{
		size_t index = GetIndex(level);
		size_t target_bit = GetBit(ip, index, level);
		int check = SUCCESS;

		if (NULL == node->children[target_bit])
		{
			return INVALID_ADDRESS;
		}

		check = FreeIp(node->children[target_bit], ip, level - 1); 

		if (INVALID_ADDRESS != check)
		{
			UpdateIsFull(node);
		}

		return check;
	}

	if (!IsFull(node))
	{
		return INVALID_ADDRESS;
	}

	node->is_full = 0;

	return SUCCESS;
}

/*****************************************************************************/

size_t DhcpCountFree(const dhcp_t *dhcp)
{
	size_t bits_available = 0;
	
	assert(NULL != dhcp);

	bits_available = GetBitsAvailable((dhcp_t *)dhcp);

	return Count(dhcp->root, bits_available);
}

static size_t Count(dhcp_node_t *node, size_t level)
{
	if (NULL == node)
	{
		return (1 << level);
	}
	else if (level > 0 && !IsFull(node))
	{
		return Count(node->children[ON], level - 1) + 
			   Count(node->children[OFF], level - 1);
	}	
	else if (!IsFull(node))
	{
		return 1;
	}

	return 0;
}
