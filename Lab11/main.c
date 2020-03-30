#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "data_store.h"

user_t** get_test_users_malloc();
void destroy_users(user_t** users);

int main(void)
{
    remove("log.txt");

    user_t** users = get_test_users_malloc();

    user_t* user = get_user_by_id_or_null(users, 2);

    assert(user->id == 2);
    assert(strcmp(user->username, "user2") == 0);
    assert(strcmp(user->email, "email2@pocustudent.academy") == 0);
    assert(strcmp(user->password, "password2") == 0);

    user = get_user_by_username_or_null(users, "user5");

    assert(user->id == 5);
    assert(strcmp(user->username, "user5") == 0);
    assert(strcmp(user->email, "email5@pocustudent.academy") == 0);
    assert(strcmp(user->password, "password5") == 0);

    assert(!update_email(users, 20, "someemail@email.com"));
    assert(!update_password(users, 20, "randompassword"));

    const char* new_email = "n@gmail.com";
    const char* new_password = "n";

    assert(update_email(users, 2, new_email));
    assert(update_password(users, 2, new_password));

    new_email = "ne@gmail.com";
    new_password = "ne";

    assert(update_email(users, 2, new_email));
    assert(update_password(users, 2, new_password));

    new_email = "newemail@gmail.com";
    new_password = "newpasswordishere";

    assert(update_email(users, 2, new_email));
    assert(update_password(users, 2, new_password));

    user = get_user_by_id_or_null(users, 2);

    assert(user->id == 2);
    assert(strcmp(user->username, "user2") == 0);
    assert(strcmp(user->email, new_email) == 0);
    assert(strcmp(user->password, new_password) == 0);

    destroy_users(users);
    printf("finished");
    return 0;
}

user_t** get_test_users_malloc()
{
    user_t** users = malloc(sizeof(user_t*) * 11);
    size_t i = 0;

    for (i = 0; i < 10; ++i) {
        char username[51];
        char password[51];
        char email[51];

        sprintf(username, "user%d", i);
        sprintf(password, "password%d", i);
        sprintf(email, "email%d@pocustudent.academy", i);

        user_t* user = malloc(sizeof(user_t));
        user->id = i;
        strcpy(user->username, username);
        strcpy(user->email, email);
        strcpy(user->password, password);

        users[i] = user;
    }

    users[i] = NULL;

    return users;
}

void destroy_users(user_t** users)
{
    if (users != NULL) {
        user_t** u = users;

        while (*u != NULL) {
            free(*u);
            u++;
        }

        free(users);
    }
}
