#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) ( if (x > y) { \
                        return x; \
                    } \
                    return y; \
                  )

#define MIN(x, y) ( if (x < y) { \
                        return y; \
                    } \
                    return x; \
                  )

#define ABS(x) (0)

#define RANGE(curr, min, max)

#define RANGE_DESC(curr, max, min)

#define SET(ary, start, count, value)

#endif /* MACROS_H */
