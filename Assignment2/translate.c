#include <stdio.h>
#include <string.h>
#include "translate.h"
#define NO_ERROR (6)
#define LINE_LENGTH (512)
#define ARGUMENT_LENGTH  (512)
#define ASCII_CODE_LENGTH (128)
#define UPPER_CASE (2)
#define LOWER_CASE (1)
#define NOT_A_LETTER (0)
#define DIFFERENCE_BETWEEN_UPPER_AND_LOWER (32)
#define NULL_CHAR ('\0')
#define WITHOUT_IGNORE_FLAG_LENGTH (3)
#define WITH_IGNORE_FLAG_LENGTH (4)


int tell_letter_case(char letter) 
{
    if (letter >= 'A' && letter <= 'Z') {
        return UPPER_CASE;
    }

    if (letter >= 'a' && letter <= 'z') {
        return LOWER_CASE;
    }

    return NOT_A_LETTER;
}

void translate_line(const char* char_from, const char* char_to, char* line, int ignore_flag)
{
    const char* tmp = char_from;
    int result;
    for (; *line != NULL_CHAR; line++) {
        for (; *tmp != NULL_CHAR; tmp++) {
            if (*tmp == *line) {
                *line = *(char_to + (tmp - char_from));
                break;
            }
            if (ignore_flag == TRUE) {
                result = tell_letter_case(*tmp);
                if (result == NOT_A_LETTER) {
                    break;
                }
                if (result == UPPER_CASE && *tmp + DIFFERENCE_BETWEEN_UPPER_AND_LOWER == (*line)) {
                    *line = *(char_to + (tmp - char_from));
                    break;
                }
                if (*tmp - DIFFERENCE_BETWEEN_UPPER_AND_LOWER == *line) {
                    *line = *(char_to + (tmp - char_from));
                    break;
                }
            }
        }
        tmp = char_from;
    }
}

int is_valid_escape_letter(char letter) 
{
    char escape_letters[] = "\\abfnrtv'\"";
    char* ptr_escape_letters = escape_letters;
    
    while (*ptr_escape_letters != '\0') {
        if (*ptr_escape_letters == letter) {
            return TRUE;
        }
        ptr_escape_letters++;
    }

    return FALSE;
}

int return_escape_letter(char letter) 
{
    switch (letter) {
    case '\\':
        return '\\';
    case 'a':
        return '\a';
    case 'b':
        return '\b';
    case 'f':
        return '\f';
    case 'n':
        return '\n';
    case 'r':
        return '\r';
    case 't':
        return '\t';
    case 'v':
        return '\v';
    case '\'':
        return '\'';
    case '\"':
        return '\"';
    default: 
        return -1;
    }
}

int try_put_escape_letter(char letter, char* dest, int* dest_length)
{
    int result = return_escape_letter(letter);
    if (result == -1) {
        return FALSE;
    }
    dest[*dest_length] = result;
    (*dest_length)++;
    
    return TRUE;
}

int try_put_letters_in_scope(char minimum_scope_char, char maximum_scope_char, char* dest, int* dest_length, int* error_type)
{
    int range = maximum_scope_char - minimum_scope_char;
    char target_letter = minimum_scope_char;

    if (minimum_scope_char == '-' && maximum_scope_char == '-') {
        dest[*dest_length] = '-';
        (*dest_length)++;
        return TRUE;
    }

    if (range + *dest_length > ARGUMENT_LENGTH) {
        *error_type = ERROR_CODE_ARGUMENT_TOO_LONG;
        return FALSE;
    }

    if (minimum_scope_char > maximum_scope_char) {
        *error_type = ERROR_CODE_INVALID_RANGE;
        return FALSE;
    }

    for (; target_letter <= maximum_scope_char; target_letter++) {
        dest[*dest_length] = target_letter;
        (*dest_length)++;
    }

    return TRUE;
}

int is_escape_letter(char letter)
{
    return letter == '\\' || letter == '\a' || letter == '\b' || letter == '\f' || letter == '\n' || letter == '\r' || letter == '\t' || letter == '\v' || letter == '\'' || letter == '\"';    
}

int translate_escape_letter_and_scope(char* dest, char* src, int* src_length, int* is_error)
{
    int index = 0;
    char* minimum_scope_ptr = NULL;
    char* maximum_scope_ptr = NULL;
    int is_scope = FALSE;
    int dest_length = 0;
    int error_type = 0;
    char minimum_scope_char = NULL_CHAR;
    char escape_letter = NULL_CHAR;
    char maximum_scope_char = NULL_CHAR;

    for (; index < *src_length; index++) {
        if (is_scope == TRUE) {
            maximum_scope_ptr = src + index;
            maximum_scope_char = *maximum_scope_ptr;

            if (*maximum_scope_ptr == '\\') {
                index++;
                escape_letter = return_escape_letter(src[index]);
                if (escape_letter == -1) {
                    return ERROR_CODE_INVALID_FORMAT;
                }
                maximum_scope_ptr++;
                maximum_scope_char = escape_letter;
            }

            if (try_put_letters_in_scope(minimum_scope_char, maximum_scope_char, dest, &dest_length, &error_type) == FALSE) {
                *is_error = TRUE;
                return error_type;
            }
            is_scope = FALSE;
            continue;
        }
        
        if (src[index] == '\\') {
            index++;
            escape_letter = return_escape_letter(src[index]);
            if (escape_letter == -1) {
                return ERROR_CODE_INVALID_FORMAT;
            }
            dest[dest_length++] = escape_letter;
            continue;
        }

        if (src[index] == '-') {
            if (index == 0 || index == *src_length - 1) {
                dest[dest_length++] = src[index];
                continue;
            }

            if (is_scope == FALSE) {
                if (maximum_scope_ptr == src + (index - 1)) {
                    dest[dest_length++] = src[index];
                    continue;
                }

                is_scope = TRUE;
                dest_length--;
                minimum_scope_ptr = src + (index - 1);
                minimum_scope_char = *minimum_scope_ptr;
                if (is_escape_letter(dest[dest_length]) == TRUE) {
                    minimum_scope_char = dest[dest_length];
                }
            }
            continue;
        }

        dest[dest_length++] = src[index];
    }

    dest[dest_length] = NULL_CHAR;
    
    *src_length = dest_length;
    return NO_ERROR;
}

int find_in_used_letters(char* used_letters, int used_letters_length, char letter)
{
    int index = 0;
    for (; index < used_letters_length; index++) {
        if (letter == used_letters[index]) {
            return TRUE;
        }
    }

    return FALSE;
}

void reverse_string(char* target_string, int target_string_length)
{
    char* start = target_string;
    char* end = target_string + target_string_length - 1;
    char tmp;

    while (start < end) {
        tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}

void shrink_sets(char* set_from, char* set_to, int* set_from_length, int* set_to_length)
{
    char used_letters[ASCII_CODE_LENGTH];
    char shrinked_set_from[ARGUMENT_LENGTH];
    char shrinked_set_to[ARGUMENT_LENGTH];
    int used_letters_length = 0;
    int shrinked_set_from_length = 0;
    int shrinked_set_to_length = 0;
    int index = *set_from_length - 1;

    for (; index >= 0; index--) {
        if (find_in_used_letters(used_letters, used_letters_length, set_from[index]) == FALSE) {
            used_letters[used_letters_length++] = set_from[index];
            shrinked_set_from[shrinked_set_from_length++] = set_from[index];
            shrinked_set_to[shrinked_set_to_length++] = set_to[index];
        }
    }
    shrinked_set_to[shrinked_set_to_length] = NULL_CHAR;
    shrinked_set_from[shrinked_set_from_length] = NULL_CHAR;

    reverse_string(shrinked_set_from, shrinked_set_from_length);
    reverse_string(shrinked_set_to, shrinked_set_to_length);

    strcpy(set_from, shrinked_set_from);
    strcpy(set_to, shrinked_set_to);
    *set_from_length = shrinked_set_from_length;
    *set_to_length = shrinked_set_to_length;
}

void translate_sets(char* set_from, char* set_to, int* set_from_length, int* set_to_length)
{

    int index = 0;
    char last_char = NULL_CHAR;
    if (*set_from_length < *set_to_length) {
        *set_to_length = *set_from_length;
        set_to[*set_to_length] = NULL_CHAR;
    }

    if (*set_from_length > *set_to_length) {
        last_char = set_to[*set_to_length - 1];
        for (index = *set_to_length; index < *set_from_length; index++) {
            set_to[index] = last_char;
        }
        set_to[index] = NULL_CHAR;
        *set_to_length = *set_from_length;
    }

    shrink_sets(set_from, set_to, set_from_length, set_to_length);
}

int translate(int argc, const char** argv)
{
    const int DEFAULT_ARGC = 3;
    int set_from_length = 0;
    int set_to_length = 0;
    int is_error = FALSE;
    char** user_input = (char**)argv;
    char* user_set_from = NULL;
    char* user_set_to = NULL;
    int set_from_result = 0;
    int set_to_result = 0;
    int ignore_flag = FALSE;

    char line[LINE_LENGTH];

    char set_from[ARGUMENT_LENGTH];
    char set_to[ARGUMENT_LENGTH];

    if (argc != WITH_IGNORE_FLAG_LENGTH && argc != WITHOUT_IGNORE_FLAG_LENGTH) {
        return ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
    }

    if (argc == WITH_IGNORE_FLAG_LENGTH && (strlen(argv[1]) < 2 || argv[1][0] != '-' )) {
        return ERROR_CODE_INVALID_FORMAT;
    }

    if (argc == WITH_IGNORE_FLAG_LENGTH && (strlen(argv[1]) > 2 || argv[1][1] != 'i')) {
        return ERROR_CODE_INVALID_FLAG;
    }

    if (argc == WITH_IGNORE_FLAG_LENGTH) {
        ignore_flag = TRUE;
    }

    set_from_length = argc == DEFAULT_ARGC ? strlen(argv[1]) : strlen(argv[2]);
    set_to_length = argc == DEFAULT_ARGC ? strlen(argv[2]) : strlen(argv[2]);

    if (set_from_length >= ARGUMENT_LENGTH || set_to_length >= ARGUMENT_LENGTH) {
        return ERROR_CODE_ARGUMENT_TOO_LONG;
    }

    user_set_from = argc == DEFAULT_ARGC ? user_input[1] : user_input[2];
    user_set_to = argc == DEFAULT_ARGC ? user_input[2] : user_input[3];

    set_from_result = translate_escape_letter_and_scope(set_from, user_set_from, &set_from_length, &is_error);
    if (is_error == TRUE) {
        return set_from_result;
    }

    set_to_result = translate_escape_letter_and_scope(set_to, user_set_to, &set_to_length, &is_error);
    if (is_error == TRUE) {
        return set_to_result;
    }

    translate_sets(set_from, set_to, &set_from_length, &set_to_length);
    
    while (TRUE) {
        if (fgets(line, LINE_LENGTH, stdin) == NULL) {
            clearerr(stdin);
            break;
        }
        translate_line(set_from, set_to, line, ignore_flag);
        fprintf(stdout, "%s", line);
    }

    return 0;
}
