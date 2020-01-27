#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "my_string.h"


int main(void)
{
    const char* str = "We all live in a yellow submarine";
    int index = index_of(str, "");
    printf("%d\n", index); 

    return 0;
}
