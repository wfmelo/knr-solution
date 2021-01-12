/*
 * Exercise 4-12
 *
 * Adapt the ideas of printd to write a recursive version of itoa; that is,
 * convert an integer into a string by calling a recursive routine.
 */
#include <stdio.h>

void itoa(int n, char s[]);

int main()
{
    char s[5];

    itoa(-123, s);
    printf("%s\n", s);
    return 0;
}

void itoa(int n, char s[])
{
    static int i = 0;

    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }
    if (n / 10)
        itoa(n / 10, s);
    s[i++] = n % 10 + '0';
    s[i] = '\0';
}
