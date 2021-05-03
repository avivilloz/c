/****************************************************************************
Title: Circular Buffer H File- Infinity Labs R&D 
Group: Ol91
Description: Library of functions to implement a Circular Buffer.
****************************************************************************/

#ifndef __CBUFFER_H_ILRD_OL91__
#define __CBUFFER_H_ILRD_OL91__

#include <sys/types.h>     /* size_t, ssize_t */

typedef struct cbuffer cbuffer_t;

/*****************************************************************************
Decription: Creates Circular Buffer and returns it.
Input: Capacity of buffer.
Output: NULL if fails to allocate or a cbuffer struct if succeeds.
*************/

cbuffer_t *CBCreate(size_t capacity);

/*****************************************************************************
Decription: Frees allocated space for Circular Buffer.
Input: Circular Buffer.
Output: -
*************/

void CBDestroy(cbuffer_t *c_buffer);

/*****************************************************************************
*Decription: Writes data (bytes) up to size of 'count', from 'src' to 'c_buffer'. 
*Input: Circular Buffer, Starting pointer to be copied to 'c_buffer', 
Quantity of bytes to be written.
*Output: Quantity of bytes written. If 'count' is bigger then free space, copy 
up until 
free space.
*************/

ssize_t CBWrite(cbuffer_t *c_buffer, const void *src, size_t count);

/*****************************************************************************
*Decription: Read data (bytes) up to size of 'count', from 'c_buffer' to 'dest'.
*Input: Circular Buffer, Starting pointer to copy 'c_buffer' to, 
Quantity of bytes to be read. 
*Output: Quantity of bytes read. If 'count' is bigger then size, read up until 
size.
*************/

ssize_t CBRead(cbuffer_t *c_buffer, void *dest, size_t count);

/*****************************************************************************
Decription: Checks if 'c_buffer' is empty.
Input: Circular Buffer.
Output: 1 if is empty, 0 if is not empty.
*************/

int CBIsEmpty(const cbuffer_t *c_buffer);

/*****************************************************************************
Decription: Checks size of c_buffer's buffer (array).
Input: Circular Buffer.
Output: Size of buffer, i.e how much memory is already written in it.
*************/

size_t CBSize(const cbuffer_t *c_buffer);

/*****************************************************************************
Decription: Checks how much free space there is in the buffer. 
Input: Circular Buffer.
Output: 0 if full or the quantity of space left if not full. 
*************/

size_t CBFreeSpace(const cbuffer_t *c_buffer);

#endif	/*__CBUFFER_H_ILRD_OL91__*/

