#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

node_t* make_node_malloc(const char* key, const int value)
{
    node_t* node_malloc = malloc(sizeof(node_t));
    int key_length = strlen(key);
    node_malloc->key = malloc(sizeof(char) * (key_length + 1));

    strcpy(node_malloc->key, key);
    node_malloc->key[key_length] = '\0';
    node_malloc->value = value;
    node_malloc->next = NULL;
    return node_malloc;
}

hashmap_t* init_hashmap_malloc(size_t length, int (*p_hash_func)(const char* key))
{
    size_t plist_index = 0;
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
    const int converted_key = hashmap->hash_func(key) % hashmap->length;
    node_t* node_ptr = hashmap->plist[converted_key];
    node_t* prev_node_ptr = node_ptr;
    if (node_ptr == NULL) {
        hashmap->plist[converted_key] = make_node_malloc(key, value);
        return TRUE;
    }

    for (; node_ptr != NULL; node_ptr = node_ptr->next) {
        if (strcmp(node_ptr->key, key) == 0) {
            return FALSE;
        }
        prev_node_ptr = node_ptr;
    }
    node_ptr = make_node_malloc(key, value);
    prev_node_ptr->next = node_ptr;
    
    return TRUE;
}

int get_value(hashmap_t* hashmap, const char* key)
{
    const int converted_key = hashmap->hash_func(key) % hashmap->length;
    node_t* node_ptr = hashmap->plist[converted_key];

    for (; node_ptr != NULL; node_ptr = node_ptr->next) {
        if (strcmp(node_ptr->key, key) == 0) {
            return node_ptr->value;
        }
    }

    return -1;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    const int converted_key = hashmap->hash_func(key) % hashmap->length;
    node_t* node_ptr = hashmap->plist[converted_key];

    for (; node_ptr != NULL; node_ptr = node_ptr->next) {
        if (strcmp(node_ptr->key, key) == 0) {
            node_ptr->value = value;
            return TRUE;
        }
    }
    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    const int converted_key = hashmap->hash_func(key) % hashmap->length;
    node_t* node_ptr = hashmap->plist[converted_key];
    node_t* prev_node_ptr = node_ptr;

    if (node_ptr != NULL && strcmp(node_ptr->key, key) == 0) {
        hashmap->plist[converted_key] = node_ptr->next;
        free(node_ptr->key);
        free(node_ptr);
        return TRUE;
    }

    for (; node_ptr != NULL; node_ptr = node_ptr->next) {
        if (strcmp(node_ptr->key, key) == 0) {
            prev_node_ptr->next = node_ptr->next;
            free(node_ptr->key);
            free(node_ptr);
            return TRUE;
        }
        prev_node_ptr = node_ptr;
    }

    return FALSE;
}

void destroy(hashmap_t* hashmap)
{
    size_t plist_index = 0;
    node_t* node_ptr = NULL;
    node_t* prev_node_ptr = node_ptr;

    for (plist_index = 0; plist_index < hashmap->length; plist_index++) {
        node_ptr = hashmap->plist[plist_index];
        while (node_ptr != NULL) {
            prev_node_ptr = node_ptr;
            node_ptr = node_ptr->next;
            free(prev_node_ptr->key);
            free(prev_node_ptr );
        }
        free(hashmap->plist[plist_index]);
    }

    free(hashmap->plist);
    free(hashmap);
}
