#include "pomoku.h"
#include <stdio.h>

int g_col = 0;
int g_row = 0;
int g_black_score = 0;
int g_white_score = 0;
int g_board[20][20];

const int G_ROW_MAX_LIMIT = 20;
const int G_ROW_MIN_LIMIT = 10;
const int G_COL_MAX_LIMIT = 20;
const int G_COL_MIN_LIMIT = 10;
const int SCORE_LIMITS = 5;

void init_game()
{
    int row = 0;
    int column = 0;

    g_col = 15;
    g_row = 15;

    for (row = 0; row < G_ROW_MAX_LIMIT; row++)
    {
        for (column = 0; column < G_COL_MAX_LIMIT; column++)
        {
            g_board[row][column] = -1;
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
    if (color == COLOR_BLACK)
    {
        return g_black_score;
    }

    if (color == COLOR_WHITE)
    {

        return g_white_score;
    }

    return -1;
}

int get_color(const size_t row, const size_t col)
{
    return g_board[row][col];
}

int is_placeable(const size_t row, const size_t col)
{
    if (row >= (size_t)g_row || col >= (size_t)g_col)
    {
        return FALSE;
    }

    if (g_board[row][col] == COLOR_BLACK || g_board[row][col] == COLOR_WHITE)
    {
        return FALSE;
    }

    return TRUE;
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    if (is_placeable(row, col) == FALSE)
    {
        return FALSE;
    }

    g_board[row][col] = color;

    calculate_score(color);

    return TRUE;
}

int set_scores(int *score)
{
    int result = 0;
    int number = SCORE_LIMITS;
    if (*score >= SCORE_LIMITS)
    {
        for (; number <= *score; number++)
        {
            result += number - SCORE_LIMITS + 1;
        }
    }

    *score = 0;

    return result;
}

int insert_row(const color_t color, const size_t row)
{
    int i, col;

    if (g_row >= G_ROW_MAX_LIMIT)
    {
        return FALSE;
    }

    for (i = g_row; i >= row; i--)
    {
        for (col = 0; col < g_col; col++)
        {
            g_board[i][col] = g_board[i - 1][col];
        }
    }

    for (col = 0; col < G_COL_MAX_LIMIT; col++)
    {
        g_board[row][col] = -1;
    }

    if (color == COLOR_BLACK)
    {
        g_black_score -= 3;
    }
    else
    {
        g_white_score -= 3;
    }

    return TRUE;
}

int insert_column(const color_t color, const size_t col)
{

    int i, row;

    if (g_col >= G_COL_MAX_LIMIT)
    {
        return FALSE;
    }

    for (i = g_col; i >= col; i--)
    {
        for (row = 0; row < g_row; row++)
        {
            g_board[row][i] = g_board[row][i - 1];
        }
    }

    for (row = 0; row < G_ROW_MAX_LIMIT; row++)
    {
        g_board[row][col] = -1;
    }

    if (color == COLOR_BLACK)
    {
        g_black_score -= 3;
    }
    else
    {
        g_white_score -= 3;
    }

    return TRUE;
}

void calculate_score(const color_t color)
{
    int row_score = 0;
    int row_counts = 0;

    int col_score = 0;
    int col_counts = 0;

    int diagonal_score = 0;
    int diagonal_counts = 0;

    int reverse_diagonal_score = 0;
    int reverse_diagonal_counts = 0;

    int row = 0;
    int col = 0;
    int startCol = col;

    /* - */
    for (row = 0; row < G_ROW_MAX_LIMIT; row++)
    {
        for (col = 0; col < G_COL_MAX_LIMIT; col++)
        {
            if (g_board[row][col] == color)
            {
                row_counts += 1;
                continue;
            }
            row_score += set_scores(&row_counts);
        }
        row_score += set_scores(&row_counts);
    }

    /* | */
    for (col = 0; col < G_ROW_MAX_LIMIT; col++)
    {
        for (row = 0; row < G_COL_MAX_LIMIT; row++)
        {
            if (g_board[row][col] == color)
            {
                col_counts += 1;
                continue;
            }
            col_score += set_scores(&col_counts);
        }
        col_score += set_scores(&col_counts);
    }

    /* / */
    for (col = 0; col < G_COL_MAX_LIMIT; col++)
    {
        startCol = col;
        for (row = 0; row < G_ROW_MAX_LIMIT; row++, startCol--)
        {
            if (startCol < 0)
            {
                break;
            }
            if (g_board[row][startCol] == color)
            {
                diagonal_counts += 1;
                continue;
            }
            diagonal_score += set_scores(&diagonal_counts);
        }
        diagonal_score += set_scores(&diagonal_counts);
    }

    /* \ */
    for (col = G_COL_MAX_LIMIT - 1; col >= 0; col--)
    {
        startCol = col;
        for (row = 0; row < G_ROW_MAX_LIMIT; row++, startCol++)
        {
            if (startCol >= G_COL_MAX_LIMIT)
            {
                break;
            }
            if (g_board[row][startCol] == color)
            {
                reverse_diagonal_counts += 1;
                continue;
            }
            reverse_diagonal_score += set_scores(&reverse_diagonal_counts);
        }
        reverse_diagonal_score += set_scores(&reverse_diagonal_counts);
    }

    if (color == COLOR_BLACK)
    {
        g_black_score = row_score + col_score + diagonal_score + reverse_diagonal_score;
        return;
    }

    g_white_score = row_score + col_score + diagonal_score + reverse_diagonal_score;
}
