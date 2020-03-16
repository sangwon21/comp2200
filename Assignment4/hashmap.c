#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, int (*p_hash_func)(const char* key)) 
{
	hashmap_t* hashmap = malloc(sizeof(hashmap_t));
	hashmap->hash_func = p_hash_func;
	hashmap->length = length;
	hashmap->plist = malloc(sizeof(node_t) * length);

	return hashmap;
}