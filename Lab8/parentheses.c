#include <stdlib.h>
#include <stdio.h>
#include "parentheses.h"

#define DEFAULT_STACK_SIZE (50)
#define DEFAULT_OPENING_PARENTHESIS ('(')
#define  ANGLED_OPENING_PARENTHESIS ('[')
#define CURLY_OPENING_PARENTHESIS ('{')
#define INEQUALITY_OPENING_PARENTHESIS ('<')
#define DEFAULT_CLOSING_PARENTHESIS (')')
#define  ANGLED_CLOSING_PARENTHESIS (']')
#define CURLY_CLOSING_PARENTHESIS ('}')
#define INEQUALTIY_CLOSING_PARENTHESIS ('>')

int* make_stack_malloc()
{
    int* stack = malloc(sizeof(char) * DEFAULT_STACK_SIZE);
    return stack;
}

int compare(const void* first, const void* second)
{
    parenthesis_t parenthesis_first = *(parenthesis_t*)first;
    parenthesis_t parenthesis_second = *(parenthesis_t*)second;
    if (parenthesis_first.opening_index > parenthesis_second.opening_index) {
        return 1;
    }

    if (parenthesis_first.opening_index < parenthesis_second.opening_index) {
        return -1;
    }
    return 0;
}

size_t get_matching_parentheses(parenthesis_t* parentheses, size_t max_size, const char* str)
{
    int* default_parenthesis_stack = make_stack_malloc();
    int* angled_parenthesis_stack = make_stack_malloc();
    int* curly_parenthesis_stack = make_stack_malloc();
    int* inequality_parenthesis_stack = make_stack_malloc();
    int default_parenthesis_count = 0;
    int angled_parenthesis_count = 0;
    int curly_parenthesis_count = 0;
    int inequality_parenthesis_count = 0;
    size_t parentheses_count = 0;
    char* str_pointer = (char*)str;

    while (*str_pointer != '\0') {
        char target_char = *str_pointer;

        if (parentheses_count >= max_size) {
            break;
        }

        if (target_char == DEFAULT_OPENING_PARENTHESIS) {
            default_parenthesis_stack[default_parenthesis_count++] = str_pointer - str;
        }
        else if (target_char == ANGLED_OPENING_PARENTHESIS) {
            angled_parenthesis_stack[angled_parenthesis_count++] = str_pointer - str;
        }
        else if (target_char == CURLY_OPENING_PARENTHESIS) {
            curly_parenthesis_stack[curly_parenthesis_count++] = str_pointer - str;
        }
        else if (target_char == INEQUALITY_OPENING_PARENTHESIS) {
            inequality_parenthesis_stack[inequality_parenthesis_count++] = str_pointer - str;
        }
        else if (target_char == DEFAULT_CLOSING_PARENTHESIS) {
            if (default_parenthesis_count == 0) {
                goto pointer_move;
            }
            parentheses[parentheses_count].opening_index = default_parenthesis_stack[--default_parenthesis_count];
            parentheses[parentheses_count++].closing_index = str_pointer - str;
        }
        else if (target_char == ANGLED_CLOSING_PARENTHESIS) {
            if (angled_parenthesis_count == 0) {
                goto pointer_move;
            }
            parentheses[parentheses_count].opening_index = angled_parenthesis_stack[--angled_parenthesis_count];
            parentheses[parentheses_count++].closing_index = str_pointer - str;
        }
        else if (target_char == CURLY_CLOSING_PARENTHESIS) {
            if (curly_parenthesis_count == 0) {
                goto pointer_move;
            }
            parentheses[parentheses_count].opening_index = curly_parenthesis_stack[--curly_parenthesis_count];
            parentheses[parentheses_count++].closing_index = str_pointer - str;
        }
        else if (target_char == INEQUALTIY_CLOSING_PARENTHESIS) {
            if (inequality_parenthesis_count == 0) {
                goto pointer_move;
            }
            parentheses[parentheses_count].opening_index = inequality_parenthesis_stack[--inequality_parenthesis_count];
            parentheses[parentheses_count++].closing_index = str_pointer - str;
        }

    pointer_move:
        str_pointer++;
    }

    free(default_parenthesis_stack);
    free(angled_parenthesis_stack);
    free(curly_parenthesis_stack);
    free(inequality_parenthesis_stack);

    qsort(parentheses, parentheses_count, sizeof(parenthesis_t), compare);

    return parentheses_count;
}
