#include <stdlib.h>
#include <string.h>
#include "todo_list.h"

todo_list_t* init_todo_list_malloc(size_t max_size)
{
    todo_list_t* todo_list_malloc = malloc(sizeof(todo_list_t));
    todo_list_malloc->max_size = max_size;
    todo_list_malloc->current_size = 0;
    todo_list_malloc->todo_nodes = malloc(sizeof(todo_node_t) * max_size);
    return todo_list_malloc;
}

void dispose(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return;
    }
    for (size_t i = 0; i < todo_list->current_size; i++) {
        free(todo_list[i].todo_nodes);
    }
    free(todo_list);
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (task == NULL || todo_list == NULL || todo_list->current_size >= todo_list->max_size) {
        return false;
    }

    char* todo_task = malloc(sizeof(char) * (strlen(task) + 1));
    strcpy(todo_task, task);
    todo_node_t todo_node_struct;
    todo_node_struct.priority = priority;
    todo_node_struct.task = todo_task;

    todo_list->todo_nodes[todo_list->current_size++] = todo_node_struct;

    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    if (todo_list == NULL || todo_list->current_size == 0) {
        return false;
    }

    int32_t max_priority = todo_list->todo_nodes[0].priority;
    size_t todo_index = 0;

    for (size_t i = 0; i < todo_list->current_size; i++) {
        if (max_priority < todo_list->todo_nodes[i].priority) {
            max_priority = todo_list->todo_nodes[i].priority;
            todo_index = i;
        }
    }

    free(todo_list->todo_nodes[todo_index].task);

    for (size_t i = todo_index; i < todo_list->current_size - 1; i++) {
        todo_list->todo_nodes[i] = todo_list->todo_nodes[i + 1];
    }

    todo_list->current_size -= 1;

    return true;
}

const char* peek_or_null(todo_list_t* todo_list)
{
	if (todo_list == NULL || todo_list->current_size == 0) {
		return NULL;
	}

	int32_t max_priority = todo_list->todo_nodes[0].priority;
    size_t todo_index = 0;

    for (size_t i = 0; i < todo_list->current_size; i++) {
        if (max_priority < todo_list->todo_nodes[i].priority) {
            max_priority = todo_list->todo_nodes[i].priority;
            todo_index = i;
        }
    }

    return todo_list->todo_nodes[todo_index].task;
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
