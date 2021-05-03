/****************************************************************************
Title: Variable Size Allocator - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Miriam
Description: Variable Size memory Allocator
*****************************************************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc */
#include "vsa.h"	/* api */

int main(void)
{
	void *buffer = malloc(200);
	vsa_t *vsa = VSAInit(buffer, 200);
	size_t largest_chunk = 0;

	void *b1 = VSAAlloc(vsa, 20);
	void *b2 = VSAAlloc(vsa, 80);
	void *b3 = VSAAlloc(vsa, 30);
	void *b4 = VSAAlloc(vsa, 60);

	printf("%p\n", b1);
	printf("%p\n", b2);
	printf("%p\n", b3);
	if (NULL != b4)		/* expect NULL, i.e it won't be printed */
	{
		printf("%p\n", b4);
	}

	largest_chunk = VSALargestChunkAvailable(vsa); /* release: 24 debug: 0 */
	printf("%lu\n", largest_chunk);

	VSAAlloc(vsa, 24);

	largest_chunk = VSALargestChunkAvailable(vsa); /* release: 0 debug: 0 */
	printf("%lu\n", largest_chunk);

	VSAFree(b1);
	VSAFree(b2);

	largest_chunk = VSALargestChunkAvailable(vsa); /* release: 112 debug: 120 */
	printf("%lu\n", largest_chunk);

	b4 = VSAAlloc(vsa, 95);

	if (NULL != b4)
	{
		printf("%p\n", b4);
	};

	largest_chunk = VSALargestChunkAvailable(vsa); /* release: 8 debug: 8 */
	printf("%lu\n", largest_chunk);

	VSAFree(b4);
		
	largest_chunk = VSALargestChunkAvailable(vsa); /* release: 112 debug: 1200 */
	printf("%lu\n", largest_chunk);

	free(buffer);

	return 0;
}
