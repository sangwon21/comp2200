#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "todo_list.h"

int main(void)
{
    todo_list_t* todo_list = init_todo_list_malloc(9);

    assert(is_empty(todo_list));

    assert(add_todo(todo_list, 10, "A"));
    assert(add_todo(todo_list, 22, "B"));
    assert(add_todo(todo_list, 3, "C"));
    assert(add_todo(todo_list, 34, "D"));
    assert(add_todo(todo_list, 20, "E"));
    assert(add_todo(todo_list, 59, "F"));
    assert(add_todo(todo_list, 60, "G"));
    assert(add_todo(todo_list, 55, "H"));
    assert(add_todo(todo_list, 22, "I"));

    assert(get_count(todo_list) == 9);
    assert(!is_empty(todo_list));

    assert(!add_todo(todo_list, -5, "J"));

    assert(get_count(todo_list) == 9);

    assert(strcmp("G", peek_or_null(todo_list)) == 0);
    assert(complete_todo(todo_list));

    assert(strcmp("F", peek_or_null(todo_list)) == 0);
    assert(complete_todo(todo_list));

    assert(strcmp("H", peek_or_null(todo_list)) == 0);
    assert(complete_todo(todo_list));

    assert(strcmp("D", peek_or_null(todo_list)) == 0);
    assert(complete_todo(todo_list));

    assert(strcmp("B", peek_or_null(todo_list)) == 0);
    assert(complete_todo(todo_list));

    assert(strcmp("I", peek_or_null(todo_list)) == 0);
    assert(complete_todo(todo_list));

    assert(strcmp("E", peek_or_null(todo_list)) == 0);
    assert(complete_todo(todo_list));

    assert(strcmp("A", peek_or_null(todo_list)) == 0);
    assert(complete_todo(todo_list));

    assert(strcmp("C", peek_or_null(todo_list)) == 0);
    assert(complete_todo(todo_list));

    assert(is_empty(todo_list));
    assert(!complete_todo(todo_list));

    dispose(todo_list);

    printf("Finished");
	return 0;
}
