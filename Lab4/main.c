#include "stdio.h"
#include "my_string.h"

int main(void)
{
    //char str[] = "Oh fappy              da  y  ";
    //printf("%s\n", str);
    //reverse(str);
    //printf("%s\n", str);
    //int index = index_of(str, "happy"); /* index: 3 */
    //printf("%d\n", index);

    // reverse_by_words(str);
    // printf("%s\n", str);

    char str[] = "Oh happy day! My lovely day!";
    printf("%s\n", tokenize(str, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    return 0;
}
