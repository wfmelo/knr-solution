/*
 * Exercise 4-14
 * 
 * Define a macro swap(t, x, y) that interchanges two arguments of type t. (
 * Block structure will help.)
 */
#include <stdio.h>

#define swap(t, x, y)    \
    { t temp;            \
        temp = x;        \
        x = y;           \
        y = temp; }

int main()
{
    int x, y;

    x = 2;
    y = 4;
    printf("x = %d; y = %d\n", x , y);
    swap(int, x, y);
    printf("x = %d; y = %d\n", x , y);
    return 0;
}

/* temp = x;
 * x = y;
 * y = temp;
 */
/* x = x + y = 2 + 4; -> 6
 * y = x - y = 6 - 4; -> 2
 * x = x - y = 6 - 2; -> 4
 */
