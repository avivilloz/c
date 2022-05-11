/****************************************************************************
Title: Hash Table
Author: Aviv Illoz
Description: Hash Table API
*****************************************************************************/

#include <stdlib.h>	/* malloc */
#include <assert.h>	/* assert */
#include <math.h>	/* pow, sqrt */

#include "hash.h"	/* api */
#include "dlist.h"	/* api */

/*****************************************************************************/

typedef struct bucket
{
	dlist_t *list;
} bucket_t;

struct hash
{
	hash_func_t hash_function;
	get_key_t get_key;
	is_match_t is_match;
	size_t capacity;
	bucket_t *table;
};

/*****************************************************************************/

enum {SUCCESS, FAILURE};

/**************************** STATIC FUNCTIONS *******************************/
/* Create */

static void Remove(void *ptr);
static bucket_t *InitTable(bucket_t *table, size_t capacity);

/*****************************************************************************/

hash_t *HTCreate(
	size_t capacity, 
	hash_func_t hash_function, 
	is_match_t is_match, 
	get_key_t get_key
)
{
	hash_t *new_ht = NULL;
	
	assert(NULL != hash_function && NULL != get_key && NULL != is_match);	
		
	new_ht = (hash_t *)malloc(sizeof(hash_t));
	if (NULL == new_ht)
	{
		return NULL;
	}

	new_ht->table = (bucket_t *)malloc(capacity * sizeof(bucket_t));
	if (NULL == new_ht->table)
	{
		Remove(new_ht);	
		return NULL;
	}

	if (NULL == InitTable(new_ht->table, capacity))
	{
		Remove(new_ht->table);
		Remove(new_ht);
		return NULL;
	}

	new_ht->capacity = capacity;
	new_ht->hash_function = hash_function;
	new_ht->get_key = get_key;
	new_ht->is_match = is_match;
	
	return new_ht;
}

static void Remove(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

static bucket_t *InitTable(bucket_t *table, size_t capacity)
{	
	if (capacity > 0)
	{
		table->list = DListCreate();
		if (NULL == table->list)
		{
			return NULL;
		}
	
		if (NULL == InitTable(table + 1, capacity - 1))
		{
			DListDestroy(table->list);
			return NULL;
		}
	}

	return table;
}

/*****************************************************************************/

void HTDestroy(hash_t *table)
{
	size_t i = 0;
	size_t capacity = 0;

	assert(NULL != table);

	for (capacity = table->capacity; i < capacity; ++i)
	{
		DListDestroy(table->table[i].list);
	}
	
	Remove(table->table);
	Remove(table);
}

/*****************************************************************************/

size_t HTSize(const hash_t *table)
{
	size_t i = 0;
	size_t counter = 0;
	size_t capacity = 0;

	assert(NULL != table);

	for (capacity = table->capacity; i < capacity; ++i)
	{
		counter += DListSize(table->table[i].list);
	}

	return counter;
}

/*****************************************************************************/

int HTIsEmpty(const hash_t *table)
{
	size_t i = 0;
	size_t capacity = 0;
	int check = 1;

	assert(NULL != table);

	for (capacity = table->capacity; 1 == check && i < capacity; ++i)
	{
		check = DListIsEmpty(table->table[i].list);
	}

	return check;
}

/*****************************************************************************/

int HTInsert(hash_t *table, void *key_value)
{
	size_t index = 0;
	dlist_t *bucket = NULL;

	assert(NULL != table);

	index = table->hash_function(table->get_key(key_value)) % table->capacity;
	bucket = table->table[index].list;
	
	DListPushBack(bucket, key_value);

	return SUCCESS;
}

/*****************************************************************************/

void HTRemove(hash_t *table, const void *key)
{
	size_t index = 0;
	dlist_t *bucket = NULL;
	dlist_iter_t to_remove;

	assert(NULL != table);

	index = table->hash_function(key) % table->capacity;
	bucket = table->table[index].list;
	to_remove = DListFind(DListBegin(bucket), 
				DListEnd(bucket), 
				table->is_match, 
				key);
	
	if (!DListIsSameIterator(DListEnd(bucket), to_remove))
	{
		DListRemove(to_remove);
	}
}

/*****************************************************************************/

void *HTFind(const hash_t *table, const void *key)
{
	size_t index = 0;
	dlist_t *bucket = NULL;
	dlist_iter_t found_element;
	void *found_element_data = NULL;

	assert(NULL != table);

	index = table->hash_function(key) % table->capacity;
	bucket = table->table[index].list;
	found_element = DListFind(DListBegin(bucket), 
				DListEnd(bucket), 
				table->is_match, 
				key);

	if (DListIsSameIterator(DListEnd(bucket), found_element))
	{
		return NULL;
	}

	/* caching */
	found_element_data = DListGetData(found_element);
	DListPushFront(bucket, found_element_data);
	DListRemove(found_element);

	return found_element_data;
}

/*****************************************************************************/

int HTForEach(hash_t *table, action_t action, void *params)
{
	size_t i = 0;
	size_t capacity = 0;
	int check = SUCCESS;

	assert(NULL != table && NULL != action);

	for (capacity = table->capacity; SUCCESS == check && i < capacity; ++i)
	{
		check = DListForEach(DListBegin(table->table[i].list), 
					DListEnd(table->table[i].list), 
					action, params);
	}

	return check;
}

/*****************************************************************************/

double HTLoadFactor(const hash_t *table)
{
	assert(NULL != table);
	return (double)HTSize(table) / table->capacity;
}

double HTStandardDeviation(const hash_t *table)
{
	size_t i = 0;
	size_t capacity = 0;
	double sd = 0;
	double load_factor = 0;

	assert(NULL != table);

	load_factor = HTLoadFactor(table);

	for (capacity = table->capacity; i < capacity; ++i)
	{
		sd += pow(DListSize(table->table[i].list) - load_factor, 2);
	}

	return sqrt(1 / (table->capacity - 1) * sd);
}


