#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include "data_store.h"

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id)
{
    if (users_or_null == NULL) {
        return NULL;
    }

    user_t** user_ptr = users_or_null;

    while (*user_ptr != NULL) {
        if ((*user_ptr)->id == id) {
            return *user_ptr;
        }
        user_ptr++;
    }

    return NULL;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    if (users_or_null == NULL) {
        return NULL;
    }

    user_t** user_ptr = users_or_null;
    while (*user_ptr != NULL) {
        if (strcmp((*user_ptr)->username, username) == 0) {
            return *user_ptr;
        }
        user_ptr++;
    }
    return NULL;
}

static char* apply_rule(char* target)
{
    int length = strlen(target);
    if (length == 1) {
        target[length - 1] = '*';
        return target;
    }

    if (length == 2) {
        target[length - 1] = '*';
        return target;
    }

    for (int i = 0; i < length; i++) {
        if (i == 0 || i == length - 1) {
            continue;
        }
        target[i] = '*';
    }

    return target;    
}

static char* convert_email(char* email)
{
    char* ptr = strtok(email, "@");
    int length = strlen(ptr);
    apply_rule(ptr);
    email[length] = '@';

    return email;
}

static char* convert_password(char* password)
{
    apply_rule(password);
    return password;
}

bool update_email(user_t** users_or_null, size_t id, const char* email)
{
    user_t* target_user = get_user_by_id_or_null(users_or_null, id);
    if (target_user == NULL) {
        return false;
    }

    FILE* file = fopen("log.txt", "a");
    char old_email[51];
    strcpy(old_email, target_user->email);
    char new_email[51];
    char garbage_email[51];
    strcpy(new_email, email);
    strcpy(garbage_email, email);
    strcpy(target_user->email, new_email);

#if defined RELEASE
    convert_email(old_email);
    convert_email(new_email);
#endif
    convert_email(garbage_email);
    fprintf(file, "TRACE: User %d updated email from \"%s\" to \"%s\"\n", target_user->id, old_email, new_email);
    fclose(file);
    return true;
}

bool update_password(user_t** users_or_null, size_t id, const char* password)
{
    user_t* target_user = get_user_by_id_or_null(users_or_null, id);
    if (target_user == NULL) {
        return false;
    }

    FILE* file = fopen("log.txt", "a");
    char old_password[51];
    strcpy(old_password, target_user->password);
    char new_password[51];
    char garbage_password[51];
    strcpy(new_password, password);
    strcpy(garbage_password, password);
    strcpy(target_user->password, new_password);

#if defined (RELEASE)
    convert_password(old_password);
    convert_password(new_password);
#endif
    convert_password(garbage_password);
    fprintf(file, "TRACE: User %d updated password from \"%s\" to \"%s\"\n", target_user->id, old_password, new_password);
    fclose(file);
    return true;
}
