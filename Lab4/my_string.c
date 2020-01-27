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
