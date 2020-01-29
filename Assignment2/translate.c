#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "translate.h"
#define LINE_LENGTH 512
#define ARGUMENT_LENGTH  (512)

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

    printf("inside try_put_escape_letter letter : %c, dest_length is : %d\n", letter, *dest_length);
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
    
    *dest_length++;
    printf("dest in the target function %c\n", dest[0]);
    printf("dest in the target function %d\n", dest[1]);
    
    return TRUE;
}

int try_put_letters_in_scope(char minimum_scope_char, char maximum_scope_char, char* dest, int* dest_length)
{
    int range = maximum_scope_char - minimum_scope_char;
    char target_letter = minimum_scope_char;

    if (minimum_scope_char == '-' && maximum_scope_char == '-') {
        dest[*dest_length] = '-';
        (*dest_length)++;
        return TRUE;
    }

    if (minimum_scope_char == '-') {
        return INVALID_RANGE;
    }

    if (range + *dest_length > ARGUMENT_LENGTH) {
        return ARGUMENT_TOO_LONG;
    }

    if (minimum_scope_char > maximum_scope_char) {
        return INVALID_RANGE;
    }

    for (; target_letter <= maximum_scope_char; target_letter++) {
        dest[*dest_length] = target_letter;
        (*dest_length)++;
    }

    return TRUE;
}

int translate_escape_letter_and_scope(char* dest, char* src, int src_length)
{
    int index = 0;
    int is_escape = FALSE;
    char* minimum_scope_ptr = NULL;
    char* maximum_scope_ptr = NULL;
    int is_scope = FALSE;
    int dest_length = 0;
    int result = 0;

    for (; index < src_length; index++) {
        if (is_escape == TRUE) {
            is_escape = FALSE;
            if (try_put_escape_letter(src[index], dest, &dest_length) == FALSE) {
                return INVALID_FORMAT;
            }
            dest_length++;
            continue;
        }

        if (is_scope == TRUE) {
            maximum_scope_ptr = src + index;
            result = try_put_letters_in_scope(*minimum_scope_ptr, *maximum_scope_ptr, dest, &dest_length);
            if (result != TRUE) {
                return result;
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


int translate(int argc, const char** argv)
{
    char line[LINE_LENGTH];
    char word[LINE_LENGTH];

    char argument1[ARGUMENT_LENGTH];
    
    char char_from[LINE_LENGTH];
    char char_to[LINE_LENGTH];
    char char_from_length = strlen(argv[1]);
    char** user_input = (char**)argv;

    strcpy(char_from, user_input[1]);
    strcpy(char_to, user_input[2]);

    int length = translate_escape_letter_and_scope(argument1, char_from, char_from_length);
    printf("length is %d\n", length);
    for(int i = 0; i < length; i++) {
        printf("%d\n", argument1[i]);
    }
    printf("argument1 is %s\n", argument1);   
    
    /*
    while (TRUE) {
        if (fgets(line, LINE_LENGTH, stdin) == NULL) {
            clearerr(stdin);
            break;
        }
        
        translate_line(char_from, char_to, line);
        fprintf(stdout, "%s", line);
        // if (sscanf(line, "%s", word) == 1) {
        //     fprintf(stdout, "%s\n", word);
        // }
    }*/
    return 0;
}
