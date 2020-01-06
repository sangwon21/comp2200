#ifndef POMOKU_H
#define POMOKU_H

#define TRUE (1)
#define FALSE (0)

typedef enum color
{
    COLOR_BLACK,
    COLOR_WHITE
} color_t;

void init_game(void);

size_t get_row_count(void);

size_t get_column_count(void);

int get_score(const color_t color);

int get_color(const size_t row, const size_t col);

int is_placeable(const size_t row, const size_t col);

int place_stone(const color_t color, const size_t row, const size_t col);

/* special moves */
int insert_row(const color_t color, const size_t row);

int insert_column(const color_t color, const size_t col);

int remove_row(const color_t color, const size_t row);

int remove_column(const color_t color, const size_t col);

int swap_rows(const color_t color, const size_t row0, size_t const row1);

int swap_columns(const color_t color, const size_t col0, const size_t col1);

int copy_row(const color_t color, const size_t src, const size_t dst);

int copy_column(const color_t color, const size_t src, const size_t dst);

int g_board[20][20];

#endif /* POMOKU_H */