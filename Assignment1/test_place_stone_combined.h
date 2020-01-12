#ifndef TEST_PLACE_STONE_COMBINED_H
#define TEST_PLACE_STONE_COMBINED_H

#include "pomoku.h"

typedef enum DIRECTION { DIRECTION_EAST, DIRECTION_WEST, DIRECTION_SOUTH, DIRECTION_NORTH } direction_t;

void test_various_score(void);
void test_place_stone_combined(void);

void test_all(void)
{
    test_various_score();
    test_place_stone_combined();
}

/* Individual Testcase */

void test_various_score(void)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int cnt = 0;
    unsigned int chain_count;
    direction_t dir = DIRECTION_EAST;

    /* Checker */
    init_game();
    for (cnt = 0; cnt < 15 * 15; cnt++) {
        i = cnt / 15;
        j = cnt % 15;
        if (cnt % 2 == 0) {
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
        }
    }
    for (cnt = 0; cnt < 15 * 15; cnt++) {
        i = cnt / 15;
        j = cnt % 15;
        if (cnt % 2 == 1) {
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
        }
    }
    assert(get_score(COLOR_BLACK) == 2162);

    /* Tornedo Pattern */
    i = 0;
    j = 0;
    init_game();
    for (cnt = 0; cnt < 15 * 15; cnt++) {
        assert(place_stone(COLOR_BLACK, i, j) == TRUE);
        switch (dir) {
            case DIRECTION_EAST:
                if (is_placeable(i, j + 1) == FALSE) {
                    dir = DIRECTION_SOUTH;
                    i++;
                } else {
                    j++;
                }
                break;
            case DIRECTION_WEST:
                if (is_placeable(i, j - 1) == FALSE) {
                    dir = DIRECTION_NORTH;
                    i--;
                } else {
                    j--;
                }
                break;
            case DIRECTION_SOUTH:
                if (is_placeable(i + 1, j) == FALSE) {
                    dir = DIRECTION_WEST;
                    j--;
                } else {
                    i++;
                }
                break;
            case DIRECTION_NORTH:
                if (is_placeable(i - 1, j) == FALSE) {
                    dir = DIRECTION_EAST;
                    j++;
                } else {
                    i--;
                }
                break;
            default:
                assert(0);
        }
    }
    assert(get_score(COLOR_BLACK) == 1521);

    /* Horizontal + Vertical + Diagonals Combained Chains of 5 stones*/
    chain_count = 5;
    for (i = 0; i <= 15 - chain_count; i++) {
        for (j = 0; j <= 15 - chain_count; j++) {
            init_game();
            assert(place_stone(COLOR_BLACK, i+2, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+2) == TRUE);
            assert(get_score(COLOR_BLACK) == 4);
        }
    }

    /* Horizontal + Vertical + Diagonals Combained Chains of 9 stones*/
    chain_count = 9;
    for (i = 0; i <= 15 - chain_count; i++) {
        for (j = 0; j <= 15 - chain_count; j++) {
            init_game();
            assert(place_stone(COLOR_BLACK, i+4, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+5) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+6) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+7) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+8) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+5, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+6, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+7, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+8, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+5, j+5) == TRUE);
            assert(place_stone(COLOR_BLACK, i+6, j+6) == TRUE);
            assert(place_stone(COLOR_BLACK, i+7, j+7) == TRUE);
            assert(place_stone(COLOR_BLACK, i+8, j+8) == TRUE);
            assert(place_stone(COLOR_BLACK, i+8, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+7, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+6, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+5, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+5) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+6) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+7) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+8) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+4) == TRUE);
            assert(get_score(COLOR_BLACK) == 20);
        }
    }
}

void test_place_stone_combined(void)
{
    unsigned int i;
    unsigned int j;
    const unsigned int MAX = 100u;
    int score = 0;

    /* Place All Positions */

    init_game();
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
            }
        }
    }
    assert(get_score(COLOR_BLACK) == 2992);

    init_game();
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
            }
        }
    }
    assert(get_score(COLOR_WHITE) == 2992);

    init_game();
    assert(place_stone(COLOR_BLACK, -1, 0) == FALSE);
    assert(place_stone(COLOR_BLACK, 0, -1) == FALSE);
    assert(place_stone(COLOR_BLACK, -1, -1) == FALSE);
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (j % 2 == 0) {
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            } else {
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
            }
        }
    }
    assert(get_score(COLOR_BLACK) == 528);
    assert(get_score(COLOR_WHITE) == 462);

        init_game();
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (i % 2 == 0) {
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
            } else {
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            }
        }
    }
    assert(get_score(COLOR_BLACK) == 462);
    assert(get_score(COLOR_WHITE) == 528);

    /* Test in Max Length */

    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_BLACK, 0, i) == TRUE);
        if (i >= 4) {
            score += i - 3;
        }
    }
    assert(get_score(COLOR_BLACK) == score);
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

    /* Test in Min Length */

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

#endif /* TEST_PLACE_STONE_COMBINED_H */
