#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

node_t* make_node_malloc()
{
    return malloc(sizeof(node_t));
}

hashmap_t* init_hashmap_malloc(size_t length, int (*p_hash_func)(const char* key)) 
{
    int plist_index = 0;
	hashmap_t* hashmap = malloc(sizeof(hashmap_t));
	hashmap->hash_func = p_hash_func;
	hashmap->length = length;
	hashmap->plist = malloc(sizeof(node_t) * length);
    for (plist_index = 0; plist_index < length; plist_index++) {
        hashmap->plist[plist_index] = NULL;
    }

	return hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    const int converted_key = hashmap->hash_func(key);
    if (hashmap->plist[converted_key] != NULL) {
        return FALSE;
    }
    hashmap->plist[converted_key] = make_node_malloc();
    hashmap->plist[converted_key]->value = value;
    return TRUE;
}

int get_value(hashmap_t* hashmap, const char* key)
{
    const int converted_key = hashmap->hash_func(key);
    if (hashmap->plist[converted_key] == NULL) {
        return -1;
    }
    return hashmap->plist[converted_key]->value;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    const int converted_key = hashmap->hash_func(key);
    if (hashmap->plist[converted_key] == NULL) {
        return FALSE;
    }
    hashmap->plist[converted_key]->value = value;
    return TRUE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    const int converted_key = hashmap->hash_func(key);
    if (hashmap->plist[converted_key] == NULL) {
        return FALSE;
    }
    free(hashmap->plist[converted_key]);
    hashmap->plist[converted_key] = NULL;
    return TRUE;
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
