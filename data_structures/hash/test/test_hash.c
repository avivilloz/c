/****************************************************************************
Title: Hash Table - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Miriam
Description: Hash Table Test API
*****************************************************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc */
#include <string.h>	/* strlen, strcmp */

#include "hash.h"	/* api */

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

/********************************* TESTS ************************************/

typedef struct person
{
	char *name;
	char *phone_number;
} person_t;

static void *GetKeyPerson(const void *person)
{
	return ((person_t *)person)->name;
}

static size_t HashStrings(const void *key)
{
	size_t sum = 0;
	size_t i = 0, size = strlen((char *)key);
	
	for (; i < size; ++i)
	{
		sum += ((char *)key)[i]; 
	}

	return sum;
}

static int IsMatchPerson(const void *lhs, const void *rhs)
{
	char *name = ((person_t *)lhs)->name;

	if (0 == strcmp(name, (char *)rhs))
	{
		return 1;
	}

	return 0;
}

static person_t *InitPersonAndInsert(hash_t *table, char *name, char *phone_number)
{
	person_t *person = (person_t *)malloc(sizeof(person_t));
	person->name = name;
	person->phone_number = phone_number;

	HTInsert(table, person);

	return person;
}

static void DestroyPeople(person_t *people[], size_t size)
{
	size_t i = 0;
	for (; i < size; ++i)
	{
		free(people[i]);
		people[i] = NULL;
	}
}

static int ChangePhoneNumber(void *data, void *params)
{
	((person_t *)data)->phone_number = (char *)params;

	return 0;
}

static test_status_t BasicTest(void)
{
	hash_t *people_table = HTCreate(10, HashStrings, IsMatchPerson, GetKeyPerson);
	person_t *people[14]; 
	char *number = "0526163171";

	expect(0 == HTSize(people_table));
	expect(1 == HTIsEmpty(people_table));
	
	people[0] = InitPersonAndInsert(people_table, "Gabriel", "1");
	people[1] = InitPersonAndInsert(people_table, "Rachel", "2");
	people[2] = InitPersonAndInsert(people_table, "Rivki", "3");
	people[3] = InitPersonAndInsert(people_table, "Mary", "4");
	people[4] = InitPersonAndInsert(people_table, "Jose", "5");
	people[5] = InitPersonAndInsert(people_table, "Jacky", "6");
	people[6] = InitPersonAndInsert(people_table, "Fruma", "7");
	people[7] = InitPersonAndInsert(people_table, "Bentzi", "8");
	people[8] = InitPersonAndInsert(people_table, "Yael", "9");
	people[9] = InitPersonAndInsert(people_table, "Beno", "10");
	people[10] = InitPersonAndInsert(people_table, "Yasmin", "11");
	people[11] = InitPersonAndInsert(people_table, "Eliza", "12");
	people[12] = InitPersonAndInsert(people_table, "Rene", "13");
	people[13] = InitPersonAndInsert(people_table, "Omri", "14");

	expect(14 == HTSize(people_table));
	expect(0 == HTIsEmpty(people_table));

	printf("%s\n", ((person_t *)HTFind(people_table, "Gabriel"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Rachel"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Rivki"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Mary"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Jose"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Jacky"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Fruma"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Bentzi"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Yael"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Beno"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Yasmin"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Eliza"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Rene"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Omri"))->phone_number);

	expect(NULL == HTFind(people_table, "Jusephina"));

	HTRemove(people_table, "Yasmin");
	HTRemove(people_table, "Gabriel");
	HTRemove(people_table, "Eliza");
	
	expect(NULL == HTFind(people_table, "Yasmin"));
	expect(NULL == HTFind(people_table, "Gabriel"));
	expect(NULL == HTFind(people_table, "Eliza"));

	expect(11 == HTSize(people_table));
	expect(0 == HTIsEmpty(people_table));

	HTForEach(people_table, ChangePhoneNumber, number);

	printf("%s\n", ((person_t *)HTFind(people_table, "Rachel"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Rivki"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Mary"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Jose"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Jacky"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Fruma"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Bentzi"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Yael"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Beno"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Rene"))->phone_number);
	printf("%s\n", ((person_t *)HTFind(people_table, "Omri"))->phone_number);

	HTDestroy(people_table);
	DestroyPeople(people, 14);

	return TEST_PASS;
}

/*****************************************************************************/

static char *words[102305];

static char *GetWord(FILE *fp)
{
	char *word = (char *)malloc(24);
	if (NULL == word)
	{
		return NULL;
	}

	if (EOF == fscanf(fp, "%s", word))
	{
		return NULL;
	}

	return word;
}

static void *GetKeyStrings(const void *key_value)
{
	return (char *)key_value;
}

static int IsMatchStrings(const void *lhs, const void *rhs)
{
	if (0 == strcmp((char *)lhs, (char *)rhs))
	{
		return 1;
	}

	return 0;
}

static test_status_t LinuxDictionary(void)
{
	/* CREATE */ 

	hash_t *dictionary = NULL;
	FILE *fp = NULL;
	size_t i = 0;

	dictionary = HTCreate(3000, HashStrings, IsMatchStrings, GetKeyStrings);
	if (NULL == dictionary)	
	{
		return TEST_FAIL;
	}

	fp = fopen("/usr/share/dict/words", "r");
	if (NULL == fp)
	{
		return TEST_FAIL;
	}

	/* TEST */

	expect(0 == HTSize(dictionary));
	expect(1 == HTIsEmpty(dictionary));

	for (; i < 102305; ++i)
	{
		words[i] = GetWord(fp);
		expect(NULL != words[i]);
		HTInsert(dictionary, words[i]);
	}

	expect(102305 == HTSize(dictionary));
	expect(0 == HTIsEmpty(dictionary));
	
	printf("%s\n", (char *)HTFind(dictionary, "études"));
	printf("%s\n", (char *)HTFind(dictionary, "A"));
	printf("%s\n", (char *)HTFind(dictionary, "zombie"));
	printf("%s\n", (char *)HTFind(dictionary, "wrist's"));
	printf("%s\n", (char *)HTFind(dictionary, "grain's"));
	printf("%s\n", (char *)HTFind(dictionary, "Thar"));
	printf("%s\n", (char *)HTFind(dictionary, "congratulatory"));

	HTRemove(dictionary, "grain's");

	expect(102304 == HTSize(dictionary));
	expect(0 == HTIsEmpty(dictionary));

	expect(NULL == HTFind(dictionary, "grain's"));

	/* DESTROY */

	for (i = 0; i < 102305; ++i)
	{
		free(words[i]);
		words[i] = NULL;
	}

	HTDestroy(dictionary);

	fclose(fp);

	return TEST_PASS; 
}

/*****************************************************************************/

int main(void)
{
	int success = TRUE;

	RUN_TEST(BasicTest());
	RUN_TEST(LinuxDictionary());

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



