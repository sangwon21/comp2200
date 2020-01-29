#ifndef TRANSLATE_H
#define TRANSLATE_H

#define TRUE (1)
#define FALSE (0)

typedef enum error_code {
    WRONG_ARGUMENTS_NUMBER = 1,
    INVALID_FLAG,
    INVALID_FORMAT,
    ARGUMENT_TOO_LONG,
    INVALID_RANGE
} error_code_t;

int translate(int argc, const char** argv);

#endif /* TRANSLATE_H */
