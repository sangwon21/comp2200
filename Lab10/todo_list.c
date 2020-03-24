#include <stdlib.h>
#include <string.h>
#include "todo_list.h"

todo_list_t* init_todo_list_malloc(size_t max_size)
{
    todo_list_t* todo_list_malloc = malloc(sizeof(todo_list_t));
    todo_list_malloc->current_size = 0;
    todo_list_malloc->max_size = max_size;
    todo_list_malloc->head = NULL;

    return todo_list_malloc;
}

void dispose(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return;
    }

    todo_node_t* todo_node_ptr = todo_list->head;
    todo_node_t* target_ptr = todo_node_ptr;
    while (todo_node_ptr != NULL) {
        target_ptr = todo_node_ptr;
        todo_node_ptr = todo_node_ptr->next;
        free(target_ptr->todo);
        free(target_ptr);
    }
    free(todo_list);
}

todo_node_t* todo_node_malloc(const int32_t priority, const char* task)
{
    todo_node_t* todo_node = malloc(sizeof(todo_node_t));
    int str_len = strlen(task);
    todo_node->todo = malloc(sizeof(char) * (str_len + 1));
    strcpy(todo_node->todo, task);
    todo_node->priority = priority;
    todo_node->prev = NULL;
    todo_node->next = NULL;
    return todo_node;
}

todo_node_t* traverse_list_to_the_end(todo_node_t* start)
{
    todo_node_t* index_ptr = start;
    while (index_ptr->next != NULL) {
        index_ptr = index_ptr->next;
    }
    return index_ptr;
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (todo_list == NULL || todo_list->current_size >= todo_list->max_size || task == NULL) {
        return false;
    }

    todo_node_t* todo_node_ptr = todo_list->head;
    todo_node_t* todo_node = todo_node_malloc(priority, task);

    todo_list->current_size += 1;

    if (todo_node_ptr == NULL) {
        todo_list->head = todo_node;
        return true;
    }

    todo_node_t* target_todo_node_ptr = traverse_list_to_the_end(todo_list->head);
    target_todo_node_ptr->next = todo_node;
    todo_node->prev = target_todo_node_ptr;
    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    if (todo_list == NULL || todo_list->current_size == 0) {
        return false;
    }

    int32_t max_priority = todo_list->head->priority;
    todo_node_t* target_todo_node = todo_list->head;
    for (todo_node_t* todo_node_ptr = todo_list->head; todo_node_ptr != NULL; todo_node_ptr = todo_node_ptr->next) {
        if (max_priority < todo_node_ptr->priority) {
            max_priority = todo_node_ptr->priority;
            target_todo_node = todo_node_ptr;
        }
    }
    todo_list->current_size -= 1;

    if (target_todo_node == todo_list->head) {
        todo_list->head = target_todo_node->next;
        if (target_todo_node->next != NULL) {
            todo_list->head->prev = NULL;
        }
        return true;
    }

    target_todo_node->prev->next = target_todo_node->next;
    if (target_todo_node->next != NULL) {
        target_todo_node->next->prev = target_todo_node->prev;
    }

    free(target_todo_node->todo);
    free(target_todo_node);
    return true;
}

const char* peek_or_null(todo_list_t* todo_list)
{
    if (todo_list->current_size == 0) {
        return NULL;
    }

    int32_t max_priority = todo_list->head->priority;
    todo_node_t* target_todo_node = todo_list->head;
    for (todo_node_t* todo_node_ptr = todo_list->head; todo_node_ptr != NULL; todo_node_ptr = todo_node_ptr->next) {
        if (max_priority < todo_node_ptr->priority) {
            max_priority = todo_node_ptr->priority;
            target_todo_node = todo_node_ptr;
        }
    }
    return target_todo_node->todo;
}

size_t get_count(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return 0;
    }
    return todo_list->current_size;
}

bool is_empty(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return true;
    }
    return todo_list->current_size == 0;
}
