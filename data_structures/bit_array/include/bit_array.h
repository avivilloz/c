/****************************************************************************
Title: Bits Array - Infinity Labs R&D 
Group: Ol91
Description: Bits array data structure for 64 bit architecture 
****************************************************************************/

#ifndef __BIT_ARRAY_ILRD_OL91__
#define __BIT_ARRAY_ILRD_OL91__

#include <stddef.h>	/* size_t */

typedef unsigned long bitsarr_t;

/* Set all the bits of bit_array to 1 */
bitsarr_t BitsArrSetAll(void);

/* Set all the bits of bit_array to 0 */
bitsarr_t BitsArrResetAll(void);

/* Set the bit number 'index' of the bit_array to 1 */
/* bit should be contain between 1 and 64 */
bitsarr_t BitsArrSetOn(bitsarr_t bit_array, size_t index);

/* Set the bit number 'index' of the bit_array to 0 */
/* index should be contain between 1 and 64 */
bitsarr_t BitsArrSetOff(bitsarr_t bit_array, size_t index);

/* Set the specific 'index' of the bit_array to set_value */
/* index should be contain between 1 and 64 */
/* boolean_value should be 0 or 1, else the behaviour of the function is undefined */
bitsarr_t BitsArrSetBit(bitsarr_t bit_array, size_t index, int boolean_value);

/* Get the value of a specific index in the bit_array, returns 1 if it is on, 0 if it is set off */
int BitsArrGetVal(bitsarr_t bit_array, size_t index);

/* Flip the values of the 'index' bit of the bit_array */
bitsarr_t BitsArrFlip(bitsarr_t bit_array, size_t index);

/* Rotate bit_array to the right num_rotation time */
bitsarr_t BitsArrRotateRight(bitsarr_t bit_array, size_t num_rotation);

/* Rotate bit_array to the left num_rotation time */
bitsarr_t BitsArrRotateLeft(bitsarr_t bit_array, size_t num_rotation);

/* Returns the number of bits 'set on' on bit_array */
size_t BitsArrCountBitsOn(bitsarr_t bit_array);

/* Returns the number of bits 'set off' on bit_array */
size_t BitsArrCountBitsOff(bitsarr_t bit_array);

/* Write the bits of bit_array as characters inside of dest array */
 /*dest should be able to contain 65 character (64 bits + '\0'), malloc, free*/
void BitsArrToString(bitsarr_t bit_array, char *dest);

/* Mirror the bit_array */
bitsarr_t BitsArrMirror(bitsarr_t bit_array);

#endif /* __BIT_ARRAY_ILRD_OL91__ */






