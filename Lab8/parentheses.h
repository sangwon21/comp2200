#ifndef PARENTHESES_H
#define PARENTHESES_H

typedef struct {
    size_t opening_index;
    size_t closing_index;
} parenthesis_t;

size_t get_matching_parentheses(parenthesis_t* parentheses, size_t max_size, const char* str);

#endif /* PARENTHESES_H */
