/****************************************************************************
Title: Vector - Infinity Labs R&D 
Group: Ol91
Author: Aviv
Reviewer: Igor
Description: Dynamic vector interface
****************************************************************************/

#include <stdio.h>
#include "dvector.h"

int main(void)
{
	int a = 32;
	int b = 52;
	int c = 85;
	int d = 100;
	int e = 124;

	/**********************/

	vector_t *vector = VectorCreate(5);
	printf("Create Vector!\n");
	printf("\nVector Capacity: %lu\n", VectorCapacity(vector));

	/**********PUSH TO POP************/

	printf("\n/**************************POP**************************/\n");
	printf("\nPush!\n");
	VectorPushBack(vector, &a);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 0));
	printf("Vector Size: %lu\n", VectorSize(vector));

	/**********************/

	printf("\nPush!\n");
	VectorPushBack(vector, &b);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 1));
	printf("Vector Size: %lu\n", VectorSize(vector));

	/**********************/

	printf("\nPush!\n");
	VectorPushBack(vector, &c);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 2));
	printf("Vector Size: %lu\n", VectorSize(vector));

	/**********************/

	printf("\nPop!\n");
	VectorPopBack(vector);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 1));
	printf("Vector Size: %lu\n", VectorSize(vector));

	/**********************/

	printf("\nPop!\n");
	VectorPopBack(vector);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 0));
	printf("Vector Size: %lu\n", VectorSize(vector));

	/**********************/

	printf("\nPop!\n");
	VectorPopBack(vector);
	printf("Vector Size: %lu\n", VectorSize(vector));

	/*********************/

	printf("\nVector Capacity: %lu\n", VectorCapacity(vector));

	/**********PUSH AND SET TO DESTROY************/

	printf("\n/*************************DESTROY*************************/\n");
	printf("\nPush Again!\n");
	VectorPushBack(vector, &a);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 0));
	printf("Vector Size: %lu\n", VectorSize(vector));

	/**********************/

	printf("\nPush Again!\n");
	VectorPushBack(vector, &b);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 1));
	printf("Vector Size: %lu\n", VectorSize(vector));

	/**********************/

	printf("\nPush Again!\n");
	VectorPushBack(vector, &c);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 2));
	printf("Vector Size: %lu\n", VectorSize(vector));

	/**********************/

	printf("\nPush Again!\n");
	VectorPushBack(vector, &d);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 3));
	printf("Vector Size: %lu\n", VectorSize(vector));

	/**********TEST SET ELEMENT************/

	printf("\nSet Element of index 3 to variable 'e'!\n");
	VectorSetElement(vector, 3, &e);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 3));
	printf("Vector Size: %lu\n", VectorSize(vector));
	
	/**********TEST IF INDEX > CAPACITY************/

	/*printf("\nSet Element of index 6 to variable 'b'!\n");

	VectorSetElement(vector, 6, &b);

	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 6));

	printf("Vector Size: %lu\n", VectorSize(vector));

	printf("Vector Capacity: %ld\n", VectorCapacity(vector));*/

	/**********RESERVE AND SHRINK************/

	printf("\nReserve 3 extra spaces!\n");
	VectorReserve(vector, 8);
	printf("Vector Size: %lu\n", VectorSize(vector));
	printf("Vector Capacity: %ld\n", VectorCapacity(vector));
	printf("\nShrink!\n");
	VectorShrinkToFit(vector);
	printf("Vector Size: %lu\n", VectorSize(vector));
	printf("Vector Capacity: %ld\n", VectorCapacity(vector));

	/**********PUSH TO TEST REALLOC************/		
	
	printf("\nNow Push! (It needs to reallocate one extra space)\n");
	VectorPushBack(vector, &d);
	printf("Get Element: %d\n", *(int *)VectorGetElement(vector, 4));
	printf("Vector Size: %lu\n", VectorSize(vector));
	printf("Vector Capacity: %ld\n", VectorCapacity(vector));

	/***********DESTROY***********/

	printf("\nDestroy!\n");
	VectorDestroy(vector);
	printf("\nDestroied.\n");
	
	/**********************/

	printf("\n/**************************END*****************************/\n");	

	return 0;
}
