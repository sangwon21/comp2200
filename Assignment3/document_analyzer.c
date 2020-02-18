#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"

#define TRUE (1)
#define FALSE (0)
#define DEFAULT_PARAGRAPH_COUNT (30)
#define DEFAULT_SENTENCE_COUNT (30)
#define DEFAULT_WORD_COUNT (30)
#define DEFAULT_WORD_LENGTH (30)

#define BUFFER_LENGTH (512)
#define SENETENCE_LENGTH (512)

char buffer[BUFFER_LENGTH];
static document_t* s_document = NULL;
static size_t s_total_word_count = 0;
static size_t s_total_sentence_count = 0;

char* make_word_malloc(char* word)
{
    char* word_malloc = malloc(sizeof(char) * DEFAULT_WORD_LENGTH);
    strcpy(word_malloc, word);
    return word_malloc;
}

void preprocess(FILE* file)
{
    char* sentence = NULL;
    char* word = NULL;
    char tmp_sentence[SENETENCE_LENGTH];
    char tmp_line[SENETENCE_LENGTH];
    char* paragraph_ptr = NULL;
    char* word_malloc = NULL;
    size_t paragraph_count = s_document->paragraph_count;
    char** target_sentence = NULL;
    int target_sentence_index = 0;
    int strtok_count = 0;

    while (TRUE) {
        if (fgets(buffer, BUFFER_LENGTH, file) == NULL) {
            clearerr(file);
            break;
        }

        if (strcmp("\n", buffer) == 0) {
            continue;
        }

        paragraph_ptr = strtok(buffer, "\n");
        if (paragraph_ptr == NULL) {
            continue;
        }

        strcpy(tmp_line, buffer);
        sentence = strtok(tmp_line, ".!?");
         
        
        while (sentence != NULL) {
            target_sentence = s_document->paragraphs[s_document->paragraph_count].sentences[s_document->paragraphs[s_document->paragraph_count].sentence_count].words;
            target_sentence_index = 0;
            strcpy(tmp_sentence, sentence);
            word = strtok(tmp_sentence, ", ");
            while (word != NULL) {
                word_malloc = make_word_malloc(word);
                target_sentence[target_sentence_index] = word_malloc;
                target_sentence_index++;
                s_total_word_count++;
                word = strtok(NULL, ", ");
            }
            s_document->paragraphs[s_document->paragraph_count].sentences[s_document->paragraphs[s_document->paragraph_count].sentence_count].word_count = target_sentence_index ;
            (s_document->paragraphs[s_document->paragraph_count].sentence_count)++;
            s_total_sentence_count++;
            strcpy(tmp_line, buffer);
            sentence = strtok(tmp_line, ".!?");
            for (strtok_count = 0; strtok_count < s_document->paragraphs[s_document->paragraph_count].sentence_count && sentence != NULL; strtok_count++) {
                sentence = strtok(NULL, ".!?");
            }
        }
        (s_document->paragraph_count)++;
    }
}

void allocate_memory()
{
    int paragraph_index = 0;
    int sentence_index = 0;
    s_document = malloc(sizeof(document_t));
    s_document->paragraph_count = 0;
    s_document->paragraphs = malloc(sizeof(paragraph_t) * DEFAULT_PARAGRAPH_COUNT);
    for (paragraph_index = 0; paragraph_index < DEFAULT_PARAGRAPH_COUNT; paragraph_index++) {
        s_document->paragraphs[paragraph_index].sentences = malloc(sizeof(sentence_t) * DEFAULT_SENTENCE_COUNT);
        s_document->paragraphs[paragraph_index].sentence_count = 0;
        for (sentence_index = 0; sentence_index < DEFAULT_SENTENCE_COUNT; sentence_index++) {
            s_document->paragraphs[paragraph_index].sentences[sentence_index].words = malloc(sizeof(char*) * DEFAULT_WORD_COUNT);
            s_document->paragraphs[paragraph_index].sentences[sentence_index].word_count = 0;
        }
    }
}

void dispose(void)
{
    int paragraph_index = 0;
    int sentence_index = 0;
    int word_index = 0;
    for (paragraph_index = 0; paragraph_index < DEFAULT_PARAGRAPH_COUNT; paragraph_index++) {
        for (sentence_index = 0; sentence_index < DEFAULT_SENTENCE_COUNT; sentence_index++) {
            for (word_index = 0; word_index < s_document->paragraphs[paragraph_index].sentences[sentence_index].word_count; word_index++) {
                free(s_document->paragraphs[paragraph_index].sentences[sentence_index].words[word_index]);
            }
            free(s_document->paragraphs[paragraph_index].sentences[sentence_index].words);
        }
        free(s_document->paragraphs[paragraph_index].sentences);
    }
    free(s_document->paragraphs);
    free(s_document);
}

int load_document(const char* document)
{
    FILE* file = fopen(document, "r");
    if (file == NULL) {
        return FALSE;
    }

    allocate_memory();
    preprocess(file);
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
    return s_document->paragraph_count;
}

const char*** get_paragraph(const size_t paragraph_index)
{
    if (s_document == NULL || paragraph_index >= s_document->paragraph_count) {
        return NULL;
    }

    return (const char***)&(s_document->paragraphs[paragraph_index].sentences->words);
}

size_t get_paragraph_word_count(const char*** paragraph)
{
    int paragraph_index = 0;
    int sentence_index = 0;
    size_t result = 0;
    if (s_document == NULL || paragraph == NULL) {
        return 0;
    }

    for (paragraph_index = 0; paragraph_index < s_document->paragraph_count; paragraph_index++) {
        if ((const char***)&s_document->paragraphs[paragraph_index].sentences->words == paragraph) {
            for (sentence_index = 0; sentence_index < s_document->paragraphs[paragraph_index].sentence_count; sentence_index++) {
                result += s_document->paragraphs[paragraph_index].sentences[sentence_index].word_count;
            }
            return result;
        }
    }

    return 0;
}   