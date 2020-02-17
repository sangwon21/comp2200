#ifndef TRANSLATE_H
#define TRANSLATE_H

#define TRUE (1)
#define FALSE (0)

typedef enum error_code {
    ERROR_CODE_WRONG_ARGUMENTS_NUMBER = 1,
    ERROR_CODE_INVALID_FLAG,
    ERROR_CODE_INVALID_FORMAT,
    ERROR_CODE_ARGUMENT_TOO_LONG,
    ERROR_CODE_INVALID_RANGE
} error_code_t;

typedef enum letter_case {
    LETTER_CASE_NOT_A_LETTER,
    LETTER_CASE_LOWER_CASE,
    LETTER_CASE_UPPER_CASE 
} letter_cast_t;

int translate(int argc, const char** argv);

#endif /* TRANSLATE_H */
