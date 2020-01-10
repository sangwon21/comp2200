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

/* custom functions */
void calculate_score(const color_t color, const size_t row, const size_t col);

int set_scores(int counts);

void subtract_scores(const color_t color, const size_t score);

int is_valid_score(const color_t color, const size_t score);

int is_insertable_row(const size_t row);

int is_insertable_col(const size_t col);

int is_removable_row(const size_t row);

int is_removable_col(const size_t col);

int is_valid_row_scope(const size_t row);

int is_valid_col_scope(const size_t col);

extern int g_board[20][20];

extern size_t g_col;

extern size_t g_row;

extern size_t g_black_score;

extern size_t g_white_score;

typedef enum status
{
    STATUS_PLACEABLE = -1,
    STATUS_NOT_ALLOWED = -2
} status_t;
#endif /* POMOKU_H */
