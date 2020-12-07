/* Exercise 1-20.
Write a program that replaces tabs in the input with the proper number of
blanks to space to the next tab stop.  Assume a fixed set of tab stops, say
every n columns.  Should n be a variable or a sybolic parameter?
*/
#include <stdio.h>
#define TAB 8 

int main()
{
    int c, n;
    
    n = TAB;
    while ((c = getchar()) != EOF) {
        if (n == 0 || c == '\n')
            n = TAB;
        if (c == '\t') {
            for (int i = 0; i < n; ++i)
                putchar(' ');
            n = TAB;
        }
        else {
            putchar(c);
            if (c != '\n')
                --n;
        }
    }
    return 0;
}
