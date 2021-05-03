/****************************************************************************
Title: Hash Table- Infinity Labs R&D 
Group: OL91
Description: Hash Table API
*****************************************************************************/
#ifndef __HASH_TABLE_ILRD_OL91__
#define __HASH_TBLE_RECURSIVE_ILRD_OL91__

#include <stddef.h>	/* size_t */

typedef size_t (*hash_func_t)(const void *key);
typedef void *(*get_key_t)(const void *key_value);
typedef int (*action_t)(void *data, void *params);
typedef int (*is_match_t)(const void *lhs, const void *rhs);
typedef struct hash hash_t;

/*****************************************************************************/
/*
Creates hash table
Input: Capacity(num of buckets), IsMatch Funtion(returns 1 if match for the key found),
 Hash Function (receives key and returns index), 
get_key function(receives key-value pair, returns the key)
Output: pointer to hash _t struct
Error: NULL if failed to allocate
Time complexity: 0(n) || 0(1)
*/
hash_t *HTCreate(
	size_t capacity, 
	hash_func_t hash_function, 
	is_match_t is_match, 
	get_key_t get_key
);

/*****************************************************************************/
/*
Decription: Destroys hash table
Input: hash table
Output: -
Error: -
Time complexity: 0(m + n) with m number of buckets, n number of elements
*/
void HTDestroy(hash_t *table);

/*****************************************************************************/
/*
Decription: Size of a hash table
Input: hash table
Output: Number of elements in a hash table
Error: - 
Time complexity: 0(n)
*/
size_t HTSize(const hash_t *table); /* Summarize the size of each bucket */

/*****************************************************************************/
/*
Decription: Determines if hash table is empty of elements or not	
Input: hash table
Output: boolian value: 1 if empty, 0 if not empty
Error: -
Time complexity: 0(m)
*/
int HTIsEmpty(const hash_t *table);

/*****************************************************************************/
/*
Decription: Inserts element in a hash table	
Input: Hash table and a  key-value pair
Output: Status
Error: Returns 1 if failed, 0 if success
Time complexity: 0(1) || 0(n) (worst case)
*/
int HTInsert(hash_t *table, void *key_value);

/*****************************************************************************/
/*
Decription: Removes element from hash table
Input: hash table and a key
Output: -
Error: -
Time complexity: 0(1) || 0(n/m) || 0(n)
*/
void HTRemove(hash_t *table, const void *key);

/*****************************************************************************/
/*
 Description: Finds element with a specific key
Input: hash table and a key
Output: Pointer to data
Error: Returns NULL pointer if not found
Time complexity: 0(1) || 0(n/m) || 0(n)
*/
void *HTFind(const hash_t *table, const void *key);

/*****************************************************************************/
/*
Decription: Performs a certain action for each element in the hash table 
Input: hash table, function with action to perform, and parameter for the action function
Output: boolian value: 1 if failed, 0 if succeeded
Error: - 
Time complexity: 0(n)
*/
int HTForEach(hash_t *table, action_t action, void *params);

/*****************************************************************************/
/*
Decription: Calculates load factor (elements per bucket)
Input: hash table
Output:load factor
Error: -
Time complexity: O(n+m)
*/
double HTLoadFactor(const hash_t *table);
double HTStandardDeviation(const hash_t *table);

#endif /*__HASH_TABLE_ILRD_OL91__*/
