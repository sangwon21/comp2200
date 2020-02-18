#ifndef DOCUMENT_ANALYZER_H
#define DOCUMENT_ANALYZER_H

#define TRUE (1)
#define FALSE (0)

int load_document(const char *document);

void dispose(void);

size_t get_total_word_count(void);

size_t get_total_sentence_count(void);

size_t get_total_paragraph_count(void);

const char*** get_paragraph(const size_t paragraph_index);

size_t get_paragraph_word_count(const char*** paragraph);

size_t get_paragraph_sentence_count(const char*** paragraph);

const char** get_sentence(const size_t paragraph_index, const size_t sentence_index);

size_t get_sentence_word_count(const char** sentence);

int print_as_tree(const char* filename);

typedef struct {
    int word_count;
    char** words;
} sentence_t;

typedef struct {
    int sentence_count;
    sentence_t* sentences;
} paragraph_t;

typedef struct {
    int paragraph_count;
    paragraph_t* paragraphs;
} document_t;

#endif /* DOCUMENT_ANALYZER_H */