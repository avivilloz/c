/****************************************************************************
Title: Circular Buffer Test
Author: Aviv Illoz
Description: Library of functions to implement a Circular Buffer.
****************************************************************************/

#include <stdio.h>	/* printf */
#include <sys/types.h> 	/* ssize_t */
#include "cbuffer.h"	/* api */

int main(void)
{
	cbuffer_t *c_buffer = CBCreate(8);
	char *src = "01234567";
	char dest[8];
	ssize_t check = 0;

	/*********************************/

	printf("************** c_buffer of capacity 8 created ****************\n");
	printf("Empty? %d\n", CBIsEmpty(c_buffer));
	printf("Size: %lu\n", CBSize(c_buffer));
	printf("Free Space: %lu\n", CBFreeSpace(c_buffer));

	/*********************************/

	printf("*************** 1- Writting 8 chars to c_buffer *******************\n"); 
	printf("How many bytes were written? %ld\n", CBWrite(c_buffer, src, 8));

	/*********************************/

	printf("Empty? %d\n", CBIsEmpty(c_buffer));
	printf("Size: %lu\n", CBSize(c_buffer));
	printf("Free Space: %lu\n", CBFreeSpace(c_buffer));

	/*********************************/

	printf("*************** 1- Reading 5 chars from c_buffer *******************\n");
	check = CBRead(c_buffer, dest, 5);
	printf("How many bytes were read? %ld\n", check);
	if (check > 0)
	{
		dest[5] = '\0';
		printf("dest now is: %s\n", dest);
	}

	/*********************************/

	printf("Empty? %d\n", CBIsEmpty(c_buffer));
	printf("Size: %lu\n", CBSize(c_buffer));
	printf("Free Space: %lu\n", CBFreeSpace(c_buffer));

	/*********************************/

	printf("*************** 2- Writting 5 chars to c_buffer *******************\n"); 
	printf("How many bytes were written? %ld\n", CBWrite(c_buffer, src, 5));

	/*********************************/

	printf("Empty? %d\n", CBIsEmpty(c_buffer));
	printf("Size: %lu\n", CBSize(c_buffer));
	printf("Free Space: %lu\n", CBFreeSpace(c_buffer));

	/*********************************/

	printf("*************** 2- Reading 8 chars from c_buffer *******************\n");
	check = CBRead(c_buffer, dest, 8);
	printf("How many bytes were read? %ld\n", check);
	if (check > 0)
	{
		printf("dest now is: %s\n", dest);
	}

	/*********************************/

	printf("Empty? %d\n", CBIsEmpty(c_buffer));
	printf("Size: %lu\n", CBSize(c_buffer));
	printf("Free Space: %lu\n", CBFreeSpace(c_buffer));

	/*********************************/

	printf("************ 3- TRY to write 9 chars to EMPTY c_buffer ***************\n"); 
	printf("How many bytes were written? %ld\n", CBWrite(c_buffer, src, 9));

	/*********************************/

	printf("Empty? %d\n", CBIsEmpty(c_buffer));
	printf("Size: %lu\n", CBSize(c_buffer));
	printf("Free Space: %lu\n", CBFreeSpace(c_buffer));

	/*********************************/

	printf("************ 4- TRY to write 2 chars to a FULL c_buffer ***************\n"); 
	printf("How many bytes were written? %ld\n", CBWrite(c_buffer, src, 2));

	/*********************************/

	printf("*************** 3- Reading 8 chars from FULL c_buffer *******************\n");
	check = CBRead(c_buffer, dest, 8);
	printf("How many bytes were read? %ld\n", check);

	/*********************************/

	printf("*************** 4- TRY Reading 2 chars from EMPTY c_buffer *******************\n");
	check = CBRead(c_buffer, dest, 2);
	printf("How many bytes were read? %ld\n", check);

	/*********************************/

	printf("************************ Destroying ***************************\n");
	CBDestroy(c_buffer);
	printf("Destroyed!\n");

	return 0;
}
