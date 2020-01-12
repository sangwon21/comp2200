#include <stdio.h>
#include <assert.h>
#include "pomoku.h"


int main(void)
{
    place_stone(COLOR_BLACK, 0, 0);
    assert(insert_column(COLOR_BLACK, -1) == FALSE);
    return 0;
}
