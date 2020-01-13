#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "array.h"

static int numbers[20] = { -1, 4, -5, 3, 10, 7, 4, 6, 5, -10, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN };

static void test_remove_at(void);
static void test_insert(void);

int main(void)
{
    assert(get_index_of(numbers, 10, 4) == 1);
    assert(get_last_index_of(numbers, 10, 4) == 6);
    assert(get_max_index(numbers, 10) == 4);
    assert(get_min_index(numbers, 10) == 9);
    test_insert();
    test_remove_at();

    return 0;
}

static void test_insert(void)
{
    size_t i;
    int expected_result[12] = { -21, -1, 4, -5, 3, 10, 7, 4, 6, 5, -10, -22 };

    assert(insert(numbers, 10, -21, 0) == TRUE);
    assert(insert(numbers, 11, -22, 11) == TRUE);

    for (i = 0; i < 12; i++)
    {
        assert(expected_result[i] == numbers[i]);
    }
}

static void test_remove_at(void)
{
    size_t i;
    int expected_result[10] = { -1, 4, -5, 3, 10, 7, 4, 6, 5, -10 };

    assert(get_index_of(numbers, 10, -21) == 0);
    assert(get_index_of(numbers, 12, -22) == 11);
    assert(remove_at(numbers, 12, 0) == TRUE);
    assert(remove_at(numbers, 11, 10) == TRUE);
    assert(get_index_of(numbers, 10, -21) == -1);
    assert(get_index_of(numbers, 10, -22) == -1);

    for (i = 0; i < 10; i++)
    {
        assert(expected_result[i] == numbers[i]);
    }
}
