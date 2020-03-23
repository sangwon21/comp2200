#include <stdlib.h>
#include "todo_list.h"

todo_list_t* init_todo_list_malloc(size_t max_size)
{
    todo_list_t* todo_list_malloc = malloc(sizeof(todo_list_t) * max_size);

    return todo_list_malloc;
}