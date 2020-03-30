#ifndef USER_H
#define USER_H

typedef struct user {
    size_t id;
    char username[51];
    char password[51];
    char email[51];
} user_t;

#endif /* USER_H */
