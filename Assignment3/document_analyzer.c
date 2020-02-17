#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "document_analyzer.h"

#define TRUE (1)
#define FALSE (0)
#define BUFFER_LENGTH (512)
#define SENETENCE_LENGTH (512)

char* buffer;
static char** s_paragraphs[SENETENCE_LENGTH];
static int s_paragraph_numbers = 0;
static char**** s_document = s_paragraphs;

void preprocess(FILE* file)
{
    while (TRUE) {
        if (fgets(buffer, BUFFER_LENGTH, file) == NULL) {
            clearerr(file);
            break;
        }
        *s_paragraphs[s_paragraph_numbers] = malloc(BUFFER_LENGTH * sizeof(char));
        if (sscanf(buffer, "%s", *s_paragraphs[s_paragraph_numbers])) {
            s_paragraph_numbers++;
        }
    } 
}

int load_document(const char *document)
{
    FILE* file = fopen(document, "r");
    if (file == NULL) {
        return FALSE;
    }
    return TRUE;
}