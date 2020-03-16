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

#define ABS(x) ( if (x < 0) { \
                    return x * -1; \
                } \
                return x;\
                )

#define RANGE(curr, min, max) (for (curr = min; curr < max + 1; curr++))

#define RANGE_DESC(curr, max, min)

#define SET(ary, start, count, value)

#endif /* MACROS_H */
