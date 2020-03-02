#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenize.h"

#define DEFAULT_TOKENIZED_LENGTH (2048)

char* split_malloc(char* str)
{
    int len = strlen(str);
    char* allocated_token = malloc(sizeof(char) * len + 1);
    strcpy(allocated_token, str);
    return allocated_token;
}


char** tokenize_malloc(const char* str, const char* delim)
{
    int str_len = strlen(str);
    char* target = malloc(sizeof(char) * str_len + 1);
    char* token = NULL;
    char** tokenized = calloc(DEFAULT_TOKENIZED_LENGTH, sizeof(char*));
    int index = 0;

    if (str_len == 0) {
        return tokenized;
    }
    
    strcpy(target, str);
    token = strtok(target, delim);

    while (token != NULL) {
        tokenized[index] = split_malloc(token);
        token = strtok(NULL, delim);
        index++;
    }

    free(target);

    return tokenized;
}
