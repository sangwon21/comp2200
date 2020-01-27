#include "stdio.h"
#include "my_string.h"

int main(void)
{
    char str[] = "Oh happy day";
    printf("%s\n", str);
    reverse(str);
    printf("%s\n", str);
    printf("Finishied");
    return 0;
}
