#include <stdlib.h>
#include "my_string.h"
#include <stdio.h>

int my_strlen(const char* str)
{
    int length = 0;

    while(*str != '\0') {
        length++;
        str++;
    }

    return length;
}

void reverse(char* str)
{
    char tmp;
    char* start = str;
    char* end = start + my_strlen(str) - 1;
    
    for(; start < end; start++, end--) {
        tmp = *start;
        *start = *end;
        *end = tmp;    
    }
}

int index_of(const char* str, const char* word)
{
    const char* str_start = str;
    const char* word_start = word;
    const char* tmp;
    for(; *str_start != '\0'; str_start++) {
        if(*str_start == *word_start) {
            tmp = str_start;
            for(; *word_start != '\0'; word_start++, tmp++) {
                if(*tmp != *word_start) {
                    goto set_up; 
                }
            }
            return str_start - str;
        }
    set_up:
        word_start = word;
    }
    return -1;
}

void reverse_by_words(char* str)
{
    char* current_position = str;
    char* sub_string_start = current_position;
    char* sub_string_end;
    char tmp;
    
    for(; *current_position != '\0'; current_position++) {
        if(*current_position != ' '){
            continue;
        }
        sub_string_end = current_position - 1;
        for(;sub_string_start < sub_string_end ;sub_string_end--, sub_string_start++){
            tmp = *sub_string_end;
            *sub_string_end = *sub_string_start;
            *sub_string_start = tmp;
        }
        sub_string_start = current_position + 1;    
    }
    if(*(current_position - 1) != ' ') {
        sub_string_end = current_position - 1;
        for(;sub_string_start < sub_string_end ;sub_string_end--, tmp++){
            tmp = *sub_string_end;
            *sub_string_end = *sub_string_start;
            *sub_string_start = tmp;
        }
    }
}
