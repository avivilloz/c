/****************************************************************************
Title: Bits Array
Author:	Aviv
Description: Bits array data structure for 64 bit architecture 
****************************************************************************/

#include <stddef.h>	/* size_t */
#include <limits.h>	/* CHAR_BIT */
#include "bit_array.h"	/* api */
#define NUM_OF_BITS (sizeof(size_t) * CHAR_BIT)

/****************************************************************************/

bitsarr_t BitsArrSetAll(void)
{
	return ~0;
}

/****************************************************************************/

bitsarr_t BitsArrResetAll(void)
{
	return 0;
}

/****************************************************************************/

bitsarr_t BitsArrSetOn(bitsarr_t bit_array, size_t index)
{		
	return bit_array | (((bit_array >> index) | 1) << index);
}

/****************************************************************************/

bitsarr_t BitsArrSetOff(bitsarr_t bit_array, size_t index)
{
	return bit_array & ~(1 << index);
}

/****************************************************************************/

bitsarr_t BitsArrSetBit(bitsarr_t bit_array, size_t index, int boolean_value)
{
	return (boolean_value) ? 
		bit_array | (((bit_array >> index) | 1) << index) :
		bit_array & ~(1 << index);
}

/****************************************************************************/

int BitsArrGetVal(bitsarr_t bit_array, size_t index)
{
	return (bit_array >> index) & 1;
}

/****************************************************************************/

bitsarr_t BitsArrFlip(bitsarr_t bit_array, size_t index)
{
	return bit_array ^ (1 << index);
}

/****************************************************************************/

bitsarr_t BitsArrRotateRight(bitsarr_t bit_array, size_t num_rotation)
{
	return (bit_array >> num_rotation) | (bit_array << (NUM_OF_BITS - num_rotation));
}

/****************************************************************************/

bitsarr_t BitsArrRotateLeft(bitsarr_t bit_array, size_t num_rotation)
{
	return (bit_array << num_rotation) | (bit_array >> (NUM_OF_BITS - num_rotation));
}

/****************************************************************************/

size_t BitsArrCountBitsOn(bitsarr_t bit_array)
{
	size_t count = 0, i = 0;

	for (; i < NUM_OF_BITS; ++i)
	{
		count += bit_array & 1;
	
		bit_array >>= 1;
	}

	return count;
}

/****************************************************************************/

size_t BitsArrCountBitsOff(bitsarr_t bit_array)
{
	size_t count = 0, i = 0;

	bit_array = ~bit_array;

	for (; i < NUM_OF_BITS; ++i)
	{
		count += bit_array & 1;
	
		bit_array >>= 1;
	}

	return count;
}

/****************************************************************************/

void BitsArrToString(bitsarr_t bit_array, char *dest)
{
	int i = NUM_OF_BITS;

	dest[i] = '\0';	

	while (i > 0)
	{
		--i;
		
		dest[i] = (bit_array & 1) + 48;

		bit_array >>= 1;
	}
}

/****************************************************************************/

bitsarr_t BitsArrMirror(bitsarr_t bit_array)
{
	int i = NUM_OF_BITS - 1, j = 0, middle = NUM_OF_BITS / 2;
	bitsarr_t result = 0;

	for (; i > middle; --i, ++j)
	{
		result |= (bit_array >> j) << i;

		result |= (bit_array << j) >> i;
	}

	return result;
}
