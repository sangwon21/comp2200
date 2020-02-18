#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "document_analyzer.h"

int main(void)
{
    const char** sentence = NULL;
    const char*** paragraph = NULL;
    size_t i = 0U;
    size_t j = 0U;
    printf("start!\n");
    assert(load_document("doesntexist.txt") == FALSE);
    assert(load_document("input.txt") == TRUE);

    dispose();
    printf("end!\n");
    return 0;
}