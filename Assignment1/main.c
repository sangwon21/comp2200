#include <stdio.h>
#include <assert.h>
#include "pomoku.h"

void test_init_game(void);
void test_horizontal_chain(void);
void test_combined_chains(void);
void test_insert_row(void);
void test_remove_row(void);
void test_swap_row(void);
void test_copy_row(void);
void score_test(void);
void init_game_and_test(void);
void score_test1(void);
void test_place_stone_combined(void);

int main(void)
{
    test_place_stone_combined();
    return 0;
}

void test_place_stone_combined(void)
{
    unsigned int i;
    unsigned int j;
    const unsigned int MAX = 100u;
    int score = 0;

    init_game();
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
            }
        }
    }

   init_game();
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
            }
        }
    }
    
    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_BLACK, 0, i) == TRUE);
        if (i >= 4) {
            score += i - 3;
        }
    }
    assert(get_score(COLOR_BLACK) == score);
    printf("score is %d\n", score);
    assert(insert_row(COLOR_BLACK, 21) == FALSE);
    assert(insert_row(COLOR_BLACK, 20) == FALSE);
    assert(insert_row(COLOR_BLACK, 19) == FALSE);
    assert(insert_row(COLOR_BLACK, 18) == FALSE);
    assert(insert_row(COLOR_BLACK, 17) == FALSE);
    assert(insert_row(COLOR_BLACK, 16) == FALSE);
    assert(insert_row(COLOR_BLACK, 15) == TRUE);
    assert(insert_row(COLOR_BLACK, 16) == TRUE);
    assert(insert_row(COLOR_BLACK, 17) == TRUE);
    assert(insert_row(COLOR_BLACK, 18) == TRUE);
    assert(insert_row(COLOR_BLACK, 19) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(insert_row(COLOR_BLACK, i) == FALSE);
    }
    assert(get_score(COLOR_BLACK) == score - 3 * 5);
    for (i = 1; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 1 && i < 20 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
            }
        }
    }

    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_WHITE, i, 0) == TRUE);
    }
    assert(insert_column(COLOR_WHITE, 21) == FALSE);
    assert(insert_column(COLOR_WHITE, 20) == FALSE);
    assert(insert_column(COLOR_WHITE, 19) == FALSE);
    assert(insert_column(COLOR_WHITE, 18) == FALSE);
    assert(insert_column(COLOR_WHITE, 17) == FALSE);
    assert(insert_column(COLOR_WHITE, 16) == FALSE);
    assert(insert_column(COLOR_WHITE, 15) == TRUE);
    assert(insert_column(COLOR_WHITE, 16) == TRUE);
    assert(insert_column(COLOR_WHITE, 17) == TRUE);
    assert(insert_column(COLOR_WHITE, 18) == TRUE);
    assert(insert_column(COLOR_WHITE, 19) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(insert_column(COLOR_WHITE, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 1; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 1 && j < 20) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
            }
        }
    }

    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_BLACK, 0, i) == TRUE);
    }
    assert(remove_row(COLOR_BLACK, 21) == FALSE);
    assert(remove_row(COLOR_BLACK, 20) == FALSE);
    assert(remove_row(COLOR_BLACK, 19) == FALSE);
    assert(remove_row(COLOR_BLACK, 18) == FALSE);
    assert(remove_row(COLOR_BLACK, 17) == FALSE);
    assert(remove_row(COLOR_BLACK, 16) == FALSE);
    assert(remove_row(COLOR_BLACK, 15) == FALSE);
    assert(remove_row(COLOR_BLACK, 14) == TRUE);
    assert(remove_row(COLOR_BLACK, 14) == FALSE);
    assert(remove_row(COLOR_BLACK, 13) == TRUE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    assert(remove_row(COLOR_BLACK, 12) == FALSE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    assert(remove_row(COLOR_BLACK, 0) == FALSE);
    for (i = 0; i <= MAX; i++) {
        assert(remove_row(COLOR_BLACK, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 10 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
            }
        }
    }

    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_WHITE, i, 0) == TRUE);
    }
    assert(remove_column(COLOR_WHITE, 21) == FALSE);
    assert(remove_column(COLOR_WHITE, 20) == FALSE);
    assert(remove_column(COLOR_WHITE, 19) == FALSE);
    assert(remove_column(COLOR_WHITE, 18) == FALSE);
    assert(remove_column(COLOR_WHITE, 17) == FALSE);
    assert(remove_column(COLOR_WHITE, 16) == FALSE);
    assert(remove_column(COLOR_WHITE, 15) == FALSE);
    assert(remove_column(COLOR_WHITE, 14) == TRUE);
    assert(remove_column(COLOR_WHITE, 14) == FALSE);
    assert(remove_column(COLOR_WHITE, 13) == TRUE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    assert(remove_column(COLOR_WHITE, 12) == FALSE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    assert(remove_column(COLOR_WHITE, 0) == FALSE);
    for (i = 0; i <= MAX; i++) {
        assert(remove_column(COLOR_WHITE, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 10) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
            }
        }
    }
}

void init_game_and_test(void)
{
    init_game();

    assert(15 == get_row_count());
    assert(15 == get_column_count());

    assert(0 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
}

void score_test1(void)
{
    /* C08_ChainsInMultipleDirections */
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 1, 0);
    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 3, 0);
    place_stone(COLOR_BLACK, 4, 0);
    place_stone(COLOR_BLACK, 5, 0);

    assert(3 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));

    place_stone(COLOR_BLACK, 5, 1);
    place_stone(COLOR_BLACK, 5, 2);
    place_stone(COLOR_BLACK, 5, 3);
    place_stone(COLOR_BLACK, 5, 4);
    place_stone(COLOR_BLACK, 5, 5);
    place_stone(COLOR_BLACK, 5, 6);

    assert(9 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));

    place_stone(COLOR_BLACK, 6, 7);
    place_stone(COLOR_BLACK, 7, 8);
    place_stone(COLOR_BLACK, 8, 9);
    place_stone(COLOR_BLACK, 9, 10);
    place_stone(COLOR_BLACK, 10, 11);

    assert(12 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));

    assert(FALSE == place_stone(COLOR_BLACK, 0, 15));
    assert(FALSE == place_stone(COLOR_BLACK, 15, 0));
    assert(FALSE == place_stone(COLOR_BLACK, 15, 15));
    assert(FALSE == place_stone(COLOR_WHITE, 0, 15));
    assert(FALSE == place_stone(COLOR_WHITE, 15, 0));
    assert(FALSE == place_stone(COLOR_WHITE, 15, 15));

    place_stone(COLOR_BLACK, 11, 11);
    place_stone(COLOR_BLACK, 12, 11);
    place_stone(COLOR_BLACK, 13, 11);
    place_stone(COLOR_BLACK, 14, 11);

    assert(13 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));

    place_stone(COLOR_BLACK, 14, 10);
    place_stone(COLOR_BLACK, 14, 12);
    place_stone(COLOR_BLACK, 14, 13);
    place_stone(COLOR_BLACK, 14, 14);

    assert(14 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));

    init_game_and_test();
    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 0);
    place_stone(COLOR_WHITE, 2, 0);
    place_stone(COLOR_WHITE, 3, 0);
    place_stone(COLOR_WHITE, 4, 0); /* 1 */
    place_stone(COLOR_WHITE, 5, 0); /* 2 */
    place_stone(COLOR_WHITE, 6, 0); /* 3 */
    place_stone(COLOR_WHITE, 7, 0);
    place_stone(COLOR_WHITE, 8, 0);
    place_stone(COLOR_WHITE, 9, 0);
    place_stone(COLOR_WHITE, 10, 0);
    place_stone(COLOR_WHITE, 11, 0);
    place_stone(COLOR_WHITE, 12, 0);
    place_stone(COLOR_WHITE, 13, 0);
    place_stone(COLOR_WHITE, 14, 0);

    assert(66 == get_score(COLOR_WHITE));
    assert(0 == get_score(COLOR_BLACK));

    place_stone(COLOR_WHITE, 5, 0);
    place_stone(COLOR_WHITE, 5, 1);
    place_stone(COLOR_WHITE, 5, 2);
    place_stone(COLOR_WHITE, 5, 3);
    place_stone(COLOR_WHITE, 5, 4);
    place_stone(COLOR_WHITE, 5, 5);
    place_stone(COLOR_WHITE, 5, 6);
    place_stone(COLOR_WHITE, 5, 7);
    place_stone(COLOR_WHITE, 5, 8);
    place_stone(COLOR_WHITE, 5, 9);
    place_stone(COLOR_WHITE, 5, 10);
    place_stone(COLOR_WHITE, 5, 11);
    place_stone(COLOR_WHITE, 5, 12);
    place_stone(COLOR_WHITE, 5, 13);
    place_stone(COLOR_WHITE, 5, 14);

    assert(132 == get_score(COLOR_WHITE));
    assert(0 == get_score(COLOR_BLACK));
}

void score_test(void)
{
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 3);
    place_stone(COLOR_BLACK, 0, 4);

    assert(1 == get_score(COLOR_BLACK));

    place_stone(COLOR_BLACK, 0, 5);

    assert(3 == get_score(COLOR_BLACK));

    place_stone(COLOR_BLACK, 0, 6);

    assert(6 == get_score(COLOR_BLACK));

    place_stone(COLOR_BLACK, 1, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 3, 3);
    place_stone(COLOR_BLACK, 4, 4);

    assert(7 == get_score(COLOR_BLACK));

    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 14);
    place_stone(COLOR_BLACK, 0, 13);
    place_stone(COLOR_BLACK, 0, 12);
    place_stone(COLOR_BLACK, 0, 11);
    place_stone(COLOR_BLACK, 0, 10);

    assert(1 == get_score(COLOR_BLACK));

    place_stone(COLOR_BLACK, 0, 9);

    assert(3 == get_score(COLOR_BLACK));

    place_stone(COLOR_BLACK, 0, 8);

    assert(6 == get_score(COLOR_BLACK));

    /* verti */
    init_game_and_test();

    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 0);
    place_stone(COLOR_WHITE, 2, 0);
    place_stone(COLOR_WHITE, 3, 0);
    place_stone(COLOR_WHITE, 4, 0);

    assert(1 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 5, 0);

    assert(3 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 6, 0);

    assert(6 == get_score(COLOR_WHITE));

    init_game_and_test();

    place_stone(COLOR_WHITE, 14, 0);
    place_stone(COLOR_WHITE, 13, 0);
    place_stone(COLOR_WHITE, 12, 0);
    place_stone(COLOR_WHITE, 11, 0);
    place_stone(COLOR_WHITE, 10, 0);

    assert(1 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 9, 0);

    assert(3 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 8, 0);

    assert(6 == get_score(COLOR_WHITE));

    /* left-diag */
    init_game_and_test();

    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 1);
    place_stone(COLOR_WHITE, 2, 2);
    place_stone(COLOR_WHITE, 3, 3);
    place_stone(COLOR_WHITE, 4, 4);

    assert(1 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 5, 5);

    assert(3 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 6, 6);

    assert(6 == get_score(COLOR_WHITE));

    init_game_and_test();

    place_stone(COLOR_WHITE, 14, 14);
    place_stone(COLOR_WHITE, 13, 13);
    place_stone(COLOR_WHITE, 12, 12);
    place_stone(COLOR_WHITE, 11, 11);
    place_stone(COLOR_WHITE, 10, 10);

    assert(1 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 9, 9);

    assert(3 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 8, 8);

    assert(6 == get_score(COLOR_WHITE));

    /* right-diag */
    init_game_and_test();

    place_stone(COLOR_WHITE, 14, 0);
    place_stone(COLOR_WHITE, 13, 1);
    place_stone(COLOR_WHITE, 12, 2);
    place_stone(COLOR_WHITE, 11, 3);
    place_stone(COLOR_WHITE, 10, 4);

    assert(1 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 9, 5);

    assert(3 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 8, 6);

    assert(6 == get_score(COLOR_WHITE));

    init_game_and_test();

    place_stone(COLOR_WHITE, 0, 14);
    place_stone(COLOR_WHITE, 1, 13);
    place_stone(COLOR_WHITE, 2, 12);
    place_stone(COLOR_WHITE, 3, 11);
    place_stone(COLOR_WHITE, 4, 10);

    assert(1 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 5, 9);

    assert(3 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 6, 8);

    assert(6 == get_score(COLOR_WHITE));
}

void test_init_game(void)
{
    init_game();

    assert(get_row_count() == 15);
    assert(get_column_count() == 15);
    assert(get_score(5) == -1);
    assert(get_score(COLOR_BLACK) == 0);
    assert(get_score(COLOR_WHITE) == 0);
}

void test_horizontal_chain(void)
{
    test_init_game();

    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 3);
    place_stone(COLOR_BLACK, 0, 4);

    assert(get_score(COLOR_BLACK) == 1);

    place_stone(COLOR_BLACK, 0, 5);
    assert(get_score(COLOR_BLACK) == 3);

    place_stone(COLOR_BLACK, 0, 7);
    assert(get_score(COLOR_BLACK) == 3);

    place_stone(COLOR_BLACK, 0, 6);
    assert(get_score(COLOR_BLACK) == 7);

    assert(get_score(COLOR_WHITE) == 0);
}

void test_combined_chains(void)
{
    test_init_game();

    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 4);
    place_stone(COLOR_BLACK, 0, 5);

    place_stone(COLOR_BLACK, 1, 3);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 3, 3);
    place_stone(COLOR_BLACK, 4, 3);

    assert(get_score(COLOR_BLACK) == 0);

    place_stone(COLOR_BLACK, 0, 3);

    assert(get_score(COLOR_BLACK) == 3);
}

void test_insert_row(void)
{
    size_t i;

    test_init_game();

    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 2, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 2, 4);
    place_stone(COLOR_BLACK, 2, 5);

    assert(get_score(COLOR_BLACK) == 3);

    assert(insert_row(COLOR_BLACK, 2) == TRUE);
    assert(get_score(COLOR_BLACK) == 0);
    assert(get_row_count() == 16);

    for (i = 0; i < 6; i++)
    {
        assert(is_placeable(2, i) == TRUE);
        assert(is_placeable(3, i) == FALSE);
    }
}

void test_remove_row(void)
{
    size_t i;

    test_init_game();

    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 2, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 2, 4);
    place_stone(COLOR_BLACK, 2, 5);

    assert(get_score(COLOR_BLACK) == 3);
    assert(remove_row(COLOR_BLACK, 2) == TRUE);
    assert(get_score(COLOR_BLACK) == 0);

    for (i = 0; i < get_column_count(); i++)
    {
        assert(is_placeable(2, i) == TRUE);
    }
}

void test_swap_row(void)
{
    size_t i;

    test_init_game();

    for (i = 0; i < 6; i++)
    {
        place_stone(COLOR_BLACK, 0, i);
    }

    assert(get_score(COLOR_BLACK) == 3);

    assert(swap_rows(COLOR_BLACK, 0, 4) == TRUE);
    assert(get_score(COLOR_BLACK) == 1);

    for (i = 0; i < 6; i++)
    {
        assert(is_placeable(0, i) == TRUE);
        assert(is_placeable(4, i) == FALSE);
    }
}

void test_copy_row(void)
{
    size_t i;

    test_init_game();

    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 2, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 2, 4);
    place_stone(COLOR_BLACK, 2, 5);
    place_stone(COLOR_BLACK, 2, 6);

    place_stone(COLOR_WHITE, 2, 7);
    place_stone(COLOR_WHITE, 2, 8);

    assert(get_score(COLOR_BLACK) == 6);
    assert(copy_row(COLOR_BLACK, 2, 4) == TRUE);
    assert(get_score(COLOR_BLACK) == 2);

    for (i = 0; i < get_column_count(); i++)
    {
        assert(get_color(4, i) == get_color(2, i));
    }
}
