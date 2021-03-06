#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"

#define TRUE (1)
#define FALSE (0)
#define DEFAULT_PARAGRAPH_COUNT (2048)
#define DEFAULT_SENTENCE_COUNT (2048)
#define DEFAULT_WORD_COUNT (2048)

#define DEFAULT_WORD_LENGTH (1024)
#define SENETENCE_LENGTH (1024)
#define BUFFER_LENGTH (1024)

static size_t s_total_word_count = 0;
static size_t s_total_sentence_count = 0;
static size_t s_total_paragraph_count = 0;
static char**** s_paragraphs;

char* make_word_malloc(char* word)
{
    char* word_malloc = malloc(sizeof(char) * DEFAULT_WORD_LENGTH);
    strcpy(word_malloc, word);
    return word_malloc;
}

char** make_sentence_malloc()
{
    char** sentence_malloc = calloc(DEFAULT_SENTENCE_COUNT, sizeof(char*));
    return sentence_malloc;
}

char*** make_paragraph_malloc()
{
    char*** paragraph_malloc = calloc(DEFAULT_SENTENCE_COUNT, sizeof(char**));
    return paragraph_malloc;
}

void make_paragraphs_malloc()
{
    s_paragraphs = calloc(DEFAULT_PARAGRAPH_COUNT, sizeof(char***));
}

void preprocess(FILE* file)
{
    char* sentence = NULL;
    char* word = NULL;
    char buffer[BUFFER_LENGTH];
    char tmp_sentence[SENETENCE_LENGTH];
    char tmp_line[SENETENCE_LENGTH];
    char* word_malloc = NULL;
    char** sentence_malloc = NULL;
    char*** paragraph_malloc = NULL;
    size_t sentence_index = 0;
    size_t paragraph_index = 0;
    size_t word_index = 0;
    size_t strtok_count = 0;

    make_paragraphs_malloc();

    while (TRUE) {
        if (fgets(buffer, BUFFER_LENGTH, file) == NULL) {
            clearerr(file);
            break;
        }

        if (strtok(buffer, "\n") == NULL) {
            continue;
        }
        paragraph_malloc = make_paragraph_malloc();
        s_paragraphs[paragraph_index] = paragraph_malloc;

        strcpy(tmp_line, buffer);
        sentence = strtok(tmp_line, ".!?");
        sentence_index = 0;

        while (sentence != NULL) {
            strcpy(tmp_sentence, sentence);
            sentence_malloc = make_sentence_malloc();
            
            word = strtok(tmp_sentence, ", ");
            word_index = 0;
            while (word != NULL) {
                word_malloc = make_word_malloc(word);
                sentence_malloc[word_index] = word_malloc;
                s_total_word_count++;
                word_index++;
                word = strtok(NULL, ", ");
            }

            strcpy(tmp_line, buffer);
            s_paragraphs[paragraph_index][sentence_index] = sentence_malloc;
            s_total_sentence_count++;
            sentence_index++;
            sentence = strtok(tmp_line, ".!?");
            for (strtok_count = 0; strtok_count < sentence_index; strtok_count++) {
                sentence = strtok(NULL, ".!?");
            }
        }
        s_total_paragraph_count++;
        paragraph_index++;
    }
}

void dispose(void)
{
    int paragraph_index = 0;
    int sentence_index = 0;
    int word_index = 0;
 
    s_total_paragraph_count = 0;
    s_total_sentence_count = 0;
    s_total_word_count = 0;

    if (s_paragraphs == NULL) {
        return;
    }

    for (paragraph_index = 0; paragraph_index < DEFAULT_PARAGRAPH_COUNT && s_paragraphs[paragraph_index] != NULL; paragraph_index++) {
        for (sentence_index = 0; sentence_index < DEFAULT_SENTENCE_COUNT && s_paragraphs[paragraph_index][sentence_index] != NULL; sentence_index++) {
            for (word_index = 0; word_index < DEFAULT_WORD_COUNT && s_paragraphs[paragraph_index][sentence_index][word_index] != NULL; word_index++) {
                free(s_paragraphs[paragraph_index][sentence_index][word_index]);
            }
            free(s_paragraphs[paragraph_index][sentence_index]);
        }
        free(s_paragraphs[paragraph_index]);
    }
    free(s_paragraphs);
    s_paragraphs = NULL;
}

int load_document(const char* document)
{
    FILE* file = fopen(document, "r");

    dispose();

    if (file == NULL) {
        return FALSE;
    }

    preprocess(file);

    fclose(file);

    return TRUE;
}

size_t get_total_word_count(void)
{
    return s_total_word_count;
}

size_t get_total_sentence_count(void)
{
    return s_total_sentence_count;
}

size_t get_total_paragraph_count(void)
{
    return s_total_paragraph_count;
}

const char*** get_paragraph(const size_t paragraph_index)
{
    if (s_paragraphs == NULL || paragraph_index >= s_total_paragraph_count) {
        return NULL;
    }
    return (const char***)s_paragraphs[paragraph_index];
}

size_t get_paragraph_word_count(const char*** paragraph)
{
    size_t sentence_index = 0;
    size_t word_index = 0;
    size_t result = 0;
    if (s_paragraphs == NULL || paragraph == NULL) {
        return 0;
    }

    for (sentence_index = 0; sentence_index < DEFAULT_SENTENCE_COUNT && paragraph[sentence_index] != NULL; sentence_index++) {
        for (word_index = 0; word_index < DEFAULT_WORD_COUNT && paragraph[sentence_index][word_index] != NULL; word_index++) {
            result++;
        }
    }

    return result;
}

size_t get_paragraph_sentence_count(const char*** paragraph)
{
    size_t sentence_index = 0;
    size_t result = 0;

    if (s_paragraphs == NULL || paragraph == NULL) {
        return 0;
    }

    for (sentence_index = 0; sentence_index < DEFAULT_SENTENCE_COUNT && paragraph[sentence_index] != NULL; sentence_index++) {
        result++;
    }

    return result;
}

const char** get_sentence(const size_t paragraph_index, const size_t sentence_index)
{
    char*** paragraph = NULL;
    size_t sentence_count = 0;

    if (s_paragraphs == NULL || paragraph_index >= s_total_paragraph_count) {
        return NULL;
    }
    paragraph = (char***)get_paragraph(paragraph_index);
    sentence_count = get_paragraph_sentence_count((const char***)paragraph);
    
    if (sentence_count <= sentence_index) {
        return NULL;
    }

    return (const char**)s_paragraphs[paragraph_index][sentence_index];
}

size_t get_sentence_word_count(const char** sentence)
{
    size_t word_index = 0;
    size_t result = 0;

    if (s_paragraphs == NULL || sentence == NULL) {
        return 0;
    }

    for (word_index = 0; word_index < DEFAULT_WORD_COUNT && sentence[word_index] != NULL; word_index++) {
        result++;
    }
    return result;
}

int print_as_tree(const char* filename)
{
    FILE* file = NULL;
    size_t paragraph_index = 0;
    size_t sentence_index = 0;
    size_t word_index = 0;
 
    if (s_paragraphs == NULL || s_total_word_count == 0) {
        return FALSE;
    }

    file = fopen(filename, "w");

    for (paragraph_index = 0; paragraph_index < s_total_paragraph_count && s_paragraphs[paragraph_index] != NULL; paragraph_index++) {
        if (paragraph_index != 0) {
            fprintf(file, "\n\n");
        }

        fprintf(file, "Paragraph %d:", paragraph_index);
        
        for (sentence_index = 0; sentence_index < DEFAULT_SENTENCE_COUNT && s_paragraphs[paragraph_index][sentence_index] != NULL; sentence_index++) {
            fprintf(file, "\n");
            fprintf(file, "    Sentence %d:", sentence_index);
            for (word_index = 0; word_index < DEFAULT_WORD_COUNT && s_paragraphs[paragraph_index][sentence_index][word_index] != NULL; word_index++) {
                fprintf(file, "\n");
                fprintf(file, "        %s", s_paragraphs[paragraph_index][sentence_index][word_index]);
            }
        }
    }

    fclose(file);
    return TRUE;
}
