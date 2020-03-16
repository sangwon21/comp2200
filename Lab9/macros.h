#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) ((x > y) ? (x) : (y)) 

#define MIN(x, y) ((x < y) ? (x) : (y))

#define ABS(x) ((x < 0) ? (x * -1) : x)

#define RANGE(curr, min, max) for (curr = min; curr < max + 1; curr++)

#define RANGE_DESC(curr, max, min) for (curr = max; curr > min - 1; curr--)

#define SET(ary, start, count, value) { \
                                        int index = start; \
                                        for (; index < start + count; index++) { \
                                            ary[index] = value; \
                                        } \
                                      } \
                                      

#endif /* MACROS_H */
