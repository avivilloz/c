/*****************************************************************************
Title: Shuffle and Sort Dictionary - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer:
Description: Shuffle and Sort Dictionary
	argv[0] -> <executable> 
	argv[1] -> <path to dict> 
	argv[2] -> <num of copies>
	argv[3] -> <seed>
******************************************************************************/

#include <stdio.h>   /* perror */
#include <stdlib.h>  /* malloc, free, atoi, srand, rand, qsort */
#include <string.h>  /* strcmp, strlen */
#include <pthread.h> /* pthread funcs */

/*****************************************************************************/

typedef unsigned int uint;

/*********************************** HELPER **********************************/

#define RETURN_IF_BAD(is_good, error_msg, ret_val) \
	if (0 == is_good) \
	{ \
		perror(error_msg); \
		return ret_val; \
	} 

static int CmpStr(const void *lhs, const void *rhs)
{
	return strcmp(*(char* const*)lhs, *(char* const*)rhs);
}

/*****************************************************************************/

#define NUM_OF_THREADS 15

static char **g_buff_copies = NULL;
static size_t g_buff_size = 0;

static size_t g_block_size = 0;

/*****************************************************************************/

/* SAS == Shuffle and Sort */
int SASDict(const char *dict_path, size_t num_of_copies, uint seed);

int main(int argc, char *argv[])
{
	RETURN_IF_BAD((0 == SASDict(argv[1], atoi(argv[2]), atoi(argv[3]))), 
				  "SASDict() - Error", 1);

	(void)argc;

	return 0;
}

/*****************************************************************************/

static char *LoadDict(const char *dict_path, size_t *_num_of_words);
static int CreateBuffCopies(
	const char *words, 
	size_t num_of_words, 
	size_t num_of_copies
);
static void ShuffleBuff(uint seed);
static int ThreadsSort(void);
static void DestroyBuffs(char *words);

int SASDict(const char *dict_path, size_t num_of_copies, uint seed)
{	
	char *words = NULL;
	size_t num_of_words = 0;

	words = LoadDict(dict_path, &num_of_words);
	RETURN_IF_BAD((NULL != words), "LoadDict() - Error", 1);

	RETURN_IF_BAD((0 == CreateBuffCopies(words, num_of_words, num_of_copies)), 
				  "CreateBuffCopies() - Error", 1);

	ShuffleBuff(seed);

	RETURN_IF_BAD((0 == ThreadsSort()), "ThreadsSort() - Error", 1);

	/* merge sorted parts */
	/* try next time doing with merge sort */
	qsort(g_buff_copies, g_buff_size, sizeof(char *), CmpStr);

	DestroyBuffs(words);

	return 0;
}

/*****************************************************************************/

static long GetFileSize(FILE *fp);
static void CopyToBuff(FILE *fp, char *words, size_t *num_of_words);

static char *LoadDict(const char *dict_path, size_t *_num_of_words)
{
	char *words = NULL;
	FILE *fp = NULL;

	fp = fopen(dict_path, "r");
	RETURN_IF_BAD((NULL != fp), "fopen() - Error", NULL);

	words = (char *)malloc(GetFileSize(fp));
	RETURN_IF_BAD((NULL != words), "malloc() - Error", NULL);

	CopyToBuff(fp, words, _num_of_words);

	fclose(fp);

	return words;
}

static long GetFileSize(FILE *fp)
{
	long file_size = 0;

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	return file_size + 1;
}

static void CopyToBuff(FILE *fp, char *words, size_t *num_of_words)
{
	char c = '\0';
	char *curr = words;

	for (c = getc(fp); EOF != c; c = getc(fp))
	{
		if ('\n' == c)
		{
			c = '\0';
			++(*num_of_words);
		}
		*curr = c;
		++curr;
	}
	*curr = '\0';
	++(*num_of_words);
}

/*****************************************************************************/

static int CreateBuffCopies(
	const char *words, 
	size_t num_of_words, 
	size_t num_of_copies
)
{
	size_t i = 0;
	const char *curr = words;

	g_buff_size = num_of_words * num_of_copies;

	g_buff_copies = (char **)malloc(g_buff_size * sizeof(char *));
	RETURN_IF_BAD((NULL != g_buff_copies), "malloc() - Error", 1);

	for (i = 0; i < g_buff_size; ++i)
	{
		if (0 == (i % num_of_words))
		{
			curr = words;
		}

		g_buff_copies[i] = (char *)curr;

		curr += (strlen(curr) + 1);
	}

	return 0;	
}

/*****************************************************************************/

static void Swap(size_t i, size_t j);

static void ShuffleBuff(uint seed) 
{
	size_t i = 0, j = 0, k = 0;

	srand(seed);

	for (i = 0; i < g_buff_size; ++i) 
	{
		j = rand() % g_buff_size;
		k = rand() % g_buff_size;

		Swap(k, j);
	}
}

static void Swap(size_t i, size_t j)
{
	char *temp = g_buff_copies[i];
	g_buff_copies[i] = g_buff_copies[j];
	g_buff_copies[j] = temp;
}

/*****************************************************************************/

static void *STSort(void *thread_index);

static int ThreadsSort(void)
{
	size_t i = 0;
	pthread_t threads[NUM_OF_THREADS];

	g_block_size = g_buff_size / NUM_OF_THREADS;

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		RETURN_IF_BAD((0 == pthread_create(&threads[i], NULL, STSort, 
					  (void *)(size_t)i)), "pthread_create() - Error", 1);
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		RETURN_IF_BAD((0 == pthread_join(threads[i], NULL)), 
					  "pthread_create() - Error", 1);
	}

	return 0;
}

static void *STSort(void *thread_index)
{
	char **block_start = g_buff_copies + ((size_t)thread_index * g_block_size);

	qsort(block_start, g_block_size, sizeof(char *), CmpStr);

	return NULL;
}

/*****************************************************************************/

static void DestroyBuffs(char *words)
{
	free(words);
	words = NULL;

	free(g_buff_copies);
	g_buff_copies = NULL;
}

/*****************************************************************************/

/*
-> printing buff

{
	size_t i = 0;

	for (; i < g_buff_size; ++i)
	{
		printf("%s\n", g_buff_copies[i]);
	}
}
*/

/*****************************************************************************/
