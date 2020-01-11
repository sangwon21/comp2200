#include "pomoku.h"
#include <stdio.h>

size_t g_col = 0;
size_t g_row = 0;
size_t g_black_score = 0;
size_t g_white_score = 0;
int g_board[20][20];

const int G_ROW_MAX_LIMIT = 20;
const int G_ROW_MIN_LIMIT = 10;
const int G_COL_MAX_LIMIT = 20;
const int G_COL_MIN_LIMIT = 10;
const int SCORE_LIMITS = 5;
const int INSERT_SCORES = 3;
const int REMOVE_SCORES = 3;
const int MINIMUM_INDEX = 0;
const int SWAP_SCORES = 2;
const int COPY_SCORES = 4;

void init_game()
{
    size_t row = 0;
    size_t col = 0;

    g_black_score = 0;
    g_white_score = 0;

    g_col = 15;
    g_row = 15;

    for (row = 0; row < G_ROW_MAX_LIMIT; row++) {
        for (col = 0; col < G_COL_MAX_LIMIT; col++) {
            if (row < g_row && col < g_col) {
                g_board[row][col] = STATUS_PLACEABLE;
                continue;
            }
            g_board[row][col] = STATUS_NOT_ALLOWED;
        }
    }
}

size_t get_row_count(void)
{
    return g_row;
}

size_t get_column_count(void)
{
    return g_col;
}

int get_score(const color_t color)
{
    if (color == COLOR_BLACK) {
        return g_black_score;
    }

    if (color == COLOR_WHITE) {

        return g_white_score;
    }

    return -1;
}

int get_color(const size_t row, const size_t col)
{
    if (row >= G_ROW_MAX_LIMIT || col >= G_COL_MAX_LIMIT) {
        return -1;
    }

    if (g_board[row][col] != COLOR_BLACK && g_board[row][col] != COLOR_WHITE) {
        return -1;
    }

    return g_board[row][col];
}

int is_placeable(const size_t row, const size_t col)
{
    if ((int)row < MINIMUM_INDEX || (int)col < MINIMUM_INDEX) {
        return FALSE;
    }

    if (row >= g_row || col >= g_col) {
        return FALSE;
    }

    if (g_board[row][col] == COLOR_BLACK || g_board[row][col] == COLOR_WHITE || g_board[row][col] == STATUS_NOT_ALLOWED) {
        return FALSE;
    }

    return TRUE;
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    if (is_placeable(row, col) == FALSE) {
        return FALSE;
    }

    if (color != COLOR_BLACK && color != COLOR_WHITE) {
        return FALSE;
    }

    g_board[row][col] = color;
    
    calculate_score(color, row, col);

    return TRUE;
}

int set_scores(int counts)
{
    int result = 0;
    if (counts >= SCORE_LIMITS) {
        result = counts - SCORE_LIMITS + 1;
    }

    return result;
}

int is_valid_score(const color_t color, const size_t score)
{
    if (color == COLOR_BLACK) {
        return g_black_score >= score;
    }

    return g_white_score >= score;
}

void subtract_scores(const color_t color, const size_t score)
{
    if (color == COLOR_BLACK) {
        g_black_score -= score;
        return;
    }

    g_white_score -= score;
}

int is_insertable_row(const size_t row)
{
    return (size_t)MINIMUM_INDEX <= row && row <= g_row && g_row < G_ROW_MAX_LIMIT;
}

int is_insertable_col(const size_t col)
{
    return (size_t)MINIMUM_INDEX <= col && col <= g_col && g_col < G_COL_MAX_LIMIT;
}

int is_removable_row(const size_t row)
{
    return (size_t)MINIMUM_INDEX <= row && row < g_row && g_row > G_ROW_MIN_LIMIT;
}

int is_removable_col(const size_t col)
{
    return (size_t)MINIMUM_INDEX <= col && col < g_col && g_col > G_COL_MIN_LIMIT;
}

int insert_row(const color_t color, const size_t row)
{
    int i;
    size_t col;

    if (is_insertable_row(row) == FALSE || is_valid_score(color, INSERT_SCORES) == FALSE) {
        return FALSE;
    }

    if (row == g_row) {
        for (col = 0; col < g_col; col++) {
            g_board[row][col] = STATUS_PLACEABLE;
        }
        return TRUE;
    }

    for (i = (int)g_row; i >= (int)row; i--) {
        for (col = 0; col < g_col; col++) {
            g_board[i][col] = g_board[i - 1][col];
        }
    }

    for (col = 0; col < g_col; col++) {
        g_board[row][col] = STATUS_PLACEABLE;
    }

    subtract_scores(color, INSERT_SCORES);
    g_row += 1;
    return TRUE;
}

int insert_column(const color_t color, const size_t col)
{

    int i;
    size_t row;

    if (is_insertable_col(col) == FALSE || is_valid_score(color, INSERT_SCORES) == FALSE) {
        return FALSE;
    }

    if (col == g_col) {
        for (row = 0; row < g_row; row++) {
            g_board[row][col] = STATUS_PLACEABLE;
        }
        return TRUE;
    }

    for (i = (int)g_col; i >= (int)col; i--) {
        for (row = 0; row < g_row; row++) {
            g_board[row][i] = g_board[row][i - 1];
        }
    }

    for (row = 0; row < g_row; row++) {
        g_board[row][col] = STATUS_PLACEABLE;
    }

    subtract_scores(color, INSERT_SCORES);
    g_col += 1;
    return TRUE;
}

int remove_row(const color_t color, const size_t row)
{
    size_t i;
    size_t col;

    if (is_removable_row(row) == FALSE || is_valid_score(color, INSERT_SCORES) == FALSE) {
        return FALSE;
    }

    for (i = row; i < g_row; i++) {
        for (col = 0; col < g_col; col++) {
            g_board[i - 1][col] = g_board[i][col];
        }
    }

    for (col = 0; col < g_col; col++) {
        g_board[g_row - 1][col] = STATUS_PLACEABLE;
    }

    subtract_scores(color, REMOVE_SCORES);
    g_row -= 1;

    return TRUE;
}

int remove_column(const color_t color, const size_t col)
{
    size_t i;
    size_t row;

    if (is_removable_col(col) == FALSE || is_valid_score(color, INSERT_SCORES) == FALSE) {
        return FALSE;
    }

    for (i = col; i < g_col; i++) {
        for (row = 0; row < g_row; row++) {
            g_board[row][i - 1] = g_board[row][i];
        }
    }

    for (row = 0; row < g_row; row++) {
        g_board[row][g_col - 1] = STATUS_PLACEABLE;
    }

    subtract_scores(color, REMOVE_SCORES);
    g_col -= 1;

    return TRUE;
}

void calculate_score(const color_t color, const size_t row, const size_t col)
{
    size_t row_counts = 0;
    size_t col_counts = 0;
    size_t diagonal_counts = 0;
    size_t reverse_diagonal_counts = 0;

    
    int row_index;
    
    int col_index;

    size_t scores;

    /* - */
    for (col_index = col; col_index < (int)g_col; ++col_index) {
        if (g_board[row][col_index] == color) {
            row_counts += 1;
            continue;
        }
        break;
    }
    
    for (row_index = row; row_index < (int)g_row; row_index++) {
        if (g_board[row_index][col] == color) {
            col_counts += 1;
            continue;
        }
        break;
    }
    
    /*
    for (col_index = (int)col; col_index >= 0; col_index -= 1) {
        if (g_board[row][col_index] == color) {
            row_counts += 1;
            continue;
        }
        break;
    }

    for (row_index = (int)row; row_index >= MINIMUM_INDEX; row_index--) {
        if (g_board[row_index][col] == color) {
            col_counts += 1;
            continue;
        }
        break;
    }


    for (col_index = col, row_index = row; col_index < (int)g_col && row_index < (int)g_row; col_index++, row_index++) {
        if (g_board[row_index][col_index] == color) {
            diagonal_counts += 1;
            continue;
        }
        break;
    }
    for (col_index = (int)col, row_index = (int)row; row_index >= MINIMUM_INDEX && col_index >= MINIMUM_INDEX; col_index--, row_index--) {
        if (g_board[row_index][col_index] == color) {
            diagonal_counts += 1;
            continue;
        }
        break;
    }
    
    for (col_index = (int)col, row_index = row; col_index >= MINIMUM_INDEX && row_index < (int)g_row; col_index--, row_index++) {
        if (g_board[row_index][col_index] == color) {
            reverse_diagonal_counts += 1;
            continue;
        }
        break;
    }

    for (col_index = col, row_index = (int)row; col_index < (int)g_col && row_index >= MINIMUM_INDEX; col_index++, row_index--) {
        if (g_board[row_index][col_index] == color) {
            reverse_diagonal_counts += 1;
            continue;
        }
        break;
    }
    */

    scores = set_scores(row_counts - 1) + set_scores(col_counts - 1) + set_scores(diagonal_counts - 1) + set_scores(reverse_diagonal_counts - 1);
    if (color == COLOR_BLACK) {
        g_black_score += scores;
        return;
    }

    g_white_score += scores;
}

int is_valid_row_scope(const size_t row)
{
    return 0 <= row && row < g_row;
}

int is_valid_col_scope(const size_t col)
{
    return 0 <= col && col < g_col;
}

int swap_rows(const color_t color, const size_t row0, size_t const row1)
{
    int col = 0;
    int tmp;
    if (is_valid_row_scope(row0) == FALSE || is_valid_row_scope(row1) == FALSE) {
        return FALSE;
    }

    if (is_valid_score(color, SWAP_SCORES) == FALSE) {
        return FALSE;
    }

    for (col = 0; col < (int)g_col; col++) {
        tmp = g_board[row0][col];
        g_board[row0][col] = g_board[row1][col];
        g_board[row1][col] = tmp;
    }

    subtract_scores(color, SWAP_SCORES);

    return TRUE;
}

int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
    int row = 0;
    int tmp;
    if (is_valid_col_scope(col0) == FALSE || is_valid_col_scope(col1) == FALSE) {
        return FALSE;
    }

    if (is_valid_score(color, SWAP_SCORES) == FALSE) {
        return FALSE;
    }

    for (row = 0; row < (int)g_row; row++) {
        tmp = g_board[row][col0];
        g_board[row][col0] = g_board[row][col1];
        g_board[row][col1] = tmp;
    }

    subtract_scores(color, SWAP_SCORES);

    return TRUE;
}

int copy_row(const color_t color, const size_t src, const size_t dst)
{
    int col = 0;

    if (is_valid_row_scope(src) == FALSE || is_valid_row_scope(dst) == FALSE) {
        return FALSE;
    }

    if (is_valid_score(color, COPY_SCORES) == FALSE) {
        return FALSE;
    }

    for (col = 0; col < (int)g_col; col++) {
        g_board[dst][col] = g_board[src][col];
    }

    subtract_scores(color, COPY_SCORES);

    return TRUE;
}

int copy_column(const color_t color, const size_t src, const size_t dst)
{
    int row = 0;

    if (is_valid_col_scope(src) == FALSE || is_valid_col_scope(dst) == FALSE) {
        return FALSE;
    }

    if (is_valid_score(color, COPY_SCORES) == FALSE) {
        return FALSE;
    }

    for (row = 0; row < (int)g_col; row++) {
        g_board[row][dst] = g_board[row][src];
    }

    subtract_scores(color, COPY_SCORES);

    return TRUE;
}
