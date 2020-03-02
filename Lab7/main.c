#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tokenize.h"

int main(void)
{
    const char* str = "I like cookies. Do you like cookies? Cookies are good!";
    char** tokens = tokenize_malloc(str, " ?!.");
    char** tt = tokens;

    assert(strcmp(*tt++, "I") == 0);
    assert(strcmp(*tt++, "like") == 0);
    assert(strcmp(*tt++, "cookies") == 0);
    assert(strcmp(*tt++, "Do") == 0);
    assert(strcmp(*tt++, "you") == 0);
    assert(strcmp(*tt++, "like") == 0);
    assert(strcmp(*tt++, "cookies") == 0);
    assert(strcmp(*tt++, "Cookies") == 0);
    assert(strcmp(*tt++, "are") == 0);
    assert(strcmp(*tt++, "good") == 0);
    assert(*tt == NULL);

    printf("failed?\n");
    tt = tokens;
    while (*tt != NULL) {
        free(*tt++);
    }

    free(tokens);
    printf("failed?\n");
    return 0;
}
