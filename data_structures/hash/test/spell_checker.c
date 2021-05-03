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

/*****************************************************************************/

static char *words[102305];

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

static void LoadLinuxDictionary(hash_t *dictionary)
{
	size_t i = 0;
	FILE *fp = fp = fopen("/usr/share/dict/words", "r");
	if (NULL == fp)
	{
		return;
	}

	for (; i < 102305; ++i)
	{
		words[i] = GetWord(fp);
		HTInsert(dictionary, words[i]);
	}

	fclose(fp);
}

static void SpellChecker(hash_t *dictionary, char *word)
{
	if (NULL == HTFind(dictionary, word))
	{
		printf("%s not found!\n", word);
		return;
	}

	printf("%s found!\n", word);
}

static void DestroyLinuxDictionary(hash_t *dictionary)
{
	size_t i = 0;	

	for (; i < 102305; ++i)
	{
		free(words[i]);
		words[i] = NULL;
	}

	HTDestroy(dictionary);
}

/*****************************************************************************/

int main(int argc, char *argv[])
{
	hash_t *dictionary = HTCreate(3000, HashStrings, IsMatchStrings, GetKeyStrings);
	if (NULL == dictionary)	
	{
		return 1;
	}

	LoadLinuxDictionary(dictionary);
	SpellChecker(dictionary, argv[argc - 1]);
	DestroyLinuxDictionary(dictionary);

	return 0;
}
