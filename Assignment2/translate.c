#include <stdio.h>
#include <string.h>
#include "translate.h"
#define NO_ERROR (6)
#define LINE_LENGTH (512)
#define ARGUMENT_LENGTH  (512)
#define ASCII_CODE_LENGTH (128)

void translate_line(const char* char_from, const char* char_to, char* line)
{
    const char* tmp = char_from;
    for (; *line != '\0' ; line++) {
        for (; *tmp != '\0'; tmp++) {
            if (*tmp == *line) {
                *line = *(char_to + (tmp - char_from));
                break;
            }
        }
        tmp = char_from;
    }
}

int tell_letter_case(char letter) 
{
    if (letter >= 'A' && letter <= 'Z') {
        return 2;
    }

    if (letter >= 'a' && letter <= 'z') {
        return 1;
    }

    return 0;
}

void translate_line_ignore_cases(const char* char_from, const char* char_to, char* line)
{
    const char* tmp = char_from;
    int result;
    for (; *line != '\0' ; line++) {
        for (; *tmp != '\0'; tmp++) {
            if (*tmp == *line) {
                *line = *(char_to + (tmp - char_from));
                break;
            }
            
            result = tell_letter_case(*tmp);
            if (result == 0) {
                break;
            }
            if (result == 2 && *tmp + 32 == (*line)) {
                *line = *(char_to + (tmp - char_from));
                break;
            }
            if (*tmp - 32 == *line) {
                *line = *(char_to + (tmp - char_from));
                break;
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

int try_put_escape_letter(char letter, char* dest, int* dest_length)
{
    switch(letter){
        case '\\':
            dest[*dest_length] = '\\';
            break;
        case 'a':
            dest[*dest_length] = '\a';
            break;
        case 'b':
            dest[*dest_length] = '\b';
            break;
        case 'f':
            dest[*dest_length] = '\f';
            break;
        case 'n':
            dest[*dest_length] = '\n';
            break;
        case 'r':
            dest[*dest_length] = '\r';
            break;
        case 't':
            dest[*dest_length] = '\t';
            break;
        case 'v':
            dest[*dest_length] = '\v';
            break;
        case '\'':
            dest[*dest_length] = '\'';
            break;
        case '\"':
            dest[*dest_length] = '\"';
            break;
        default: 
            return FALSE;
    }

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
        *error_type = ARGUMENT_TOO_LONG;
        return FALSE;
    }

    if (minimum_scope_char > maximum_scope_char) {
        *error_type = INVALID_RANGE;
        return FALSE;
    }

    for (; target_letter <= maximum_scope_char; target_letter++) {
        dest[*dest_length] = target_letter;
        (*dest_length)++;
    }

    return TRUE;
}

int translate_escape_letter_and_scope(char* dest, char* src, int src_length, int* is_error)
{
    int index = 0;
    int is_escape = FALSE;
    char* minimum_scope_ptr = NULL;
    char* maximum_scope_ptr = NULL;
    int is_scope = FALSE;
    int dest_length = 0;
    int error_type = 0;

    for (; index < src_length; index++) {
        if (is_escape == TRUE) {
            is_escape = FALSE;
            if (try_put_escape_letter(src[index], dest, &dest_length) == FALSE) {
                *is_error = TRUE;
                return INVALID_FORMAT;
            }
            continue;
        }

        if (is_scope == TRUE) {
            maximum_scope_ptr = src + index;
            if (try_put_letters_in_scope(*minimum_scope_ptr, *maximum_scope_ptr, dest, &dest_length, &error_type) == FALSE) {
                *is_error = TRUE;
                return error_type;
            }
            is_scope = FALSE;
            continue;
        }
        
        if (src[index] == '\\') {
            is_escape = TRUE;
            continue;
        }

        if (src[index] == '-') {
            if (index == 0 || index == src_length - 1) {
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
            }
            continue;
        }

        dest[dest_length++] = src[index];
    }

    dest[dest_length] = '\0';
    
    return dest_length;
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
    shrinked_set_to[shrinked_set_to_length] = '\0';
    shrinked_set_from[shrinked_set_from_length] = '\0';

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
    char last_char = '\0';
    if (*set_from_length < *set_to_length) {
        *set_to_length = *set_from_length;
        set_to[*set_to_length] = '\0';
    }

    if (*set_from_length > *set_to_length) {
        last_char = set_to[*set_to_length - 1];
        for (index = *set_to_length; index < *set_from_length; index++) {
            set_to[index] = last_char;
        }
        set_to[index] = '\0';
        *set_to_length = *set_from_length;
    }

    shrink_sets(set_from, set_to, set_from_length, set_to_length);
}

int translate(int argc, const char** argv)
{
    const int DEFAULT_ARGC = 3;
    int set_from_length = argc == DEFAULT_ARGC ? strlen(argv[1]) : strlen(argv[2]);
    int set_to_length = argc == DEFAULT_ARGC ? strlen(argv[2]) : strlen(argv[2]);
    int is_error = FALSE;
    char** user_input = (char**)argv;
    char* user_set_from = argc == DEFAULT_ARGC ? user_input[1] : user_input[2];
    char* user_set_to = argc == DEFAULT_ARGC ? user_input[2] : user_input[3];
    int set_from_result = 0;
    int set_to_result = 0;

    char line[LINE_LENGTH];

    char set_from[ARGUMENT_LENGTH];
    char set_to[ARGUMENT_LENGTH];

    if (argc != 3 && argc != 4) {
        return WRONG_ARGUMENTS_NUMBER;
    }

    if (argc == 4 && (strlen(argv[1]) < 2 || argv[1][0] != '-' )) {
        return INVALID_FORMAT;
    }

    if (argc == 4 && (strlen(argv[1]) > 2 || argv[1][1] != 'i')) {
        return INVALID_FLAG;
    }
    
    set_from_result = translate_escape_letter_and_scope(set_from, user_set_from, set_from_length, &is_error);
    if (is_error == TRUE) {
        return set_from_result;
    }

    set_to_result = translate_escape_letter_and_scope(set_to, user_set_to, set_to_length, &is_error);
    if (is_error == TRUE) {
        return set_to_result;
    }

    translate_sets(set_from, set_to, &set_from_result, &set_to_result);
    
    
    while (TRUE) {
        if (fgets(line, LINE_LENGTH, stdin) == NULL) {
            clearerr(stdin);
            break;
        }
        argc == DEFAULT_ARGC ? translate_line(set_from, set_to, line) : translate_line_ignore_cases(set_from, set_to, line);
        fprintf(stdout, "%s", line);
    }

    return 0;
}
