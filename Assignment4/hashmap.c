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

void destroy(hashmap_t* hashmap)
{
    int plist_index = 0;
    if (hashmap == NULL) {
        return;
    }

    if (hashmap->plist == NULL) {
        free(hashmap);
        return;
    }

    for (plist_index = 0; plist_index < hashmap->length; plist_index++) {
        free(hashmap->plist[plist_index]);
    }

    free(hashmap->plist);
    free(hashmap);
}