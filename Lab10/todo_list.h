#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <stdint.h>
#include <stdbool.h>

typedef struct todo_node {
    int32_t priority;
    char* task;
} todo_node_t;


typedef struct todo_list {
    size_t max_size;
    size_t current_size;
    todo_node_t* todo_nodes;
} todo_list_t;

todo_list_t* init_todo_list_malloc(size_t max_size);

void dispose(todo_list_t* todo_list);

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task);

bool complete_todo(todo_list_t* todo_list);

const char* peek_or_null(todo_list_t* todo_list);

size_t get_count(todo_list_t* todo_list);

bool is_empty(todo_list_t* todo_list);

#endif /* TODO_LIST_H */
