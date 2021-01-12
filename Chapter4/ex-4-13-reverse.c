/*
 * Exercise 4-13
 *
 * Write a recursive version of the function reverse(s), which reverses the
 * string s in place.
 */
#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main()
{
    char s[] = "!dlrow ,olleH";

    reverse(s);
    printf("%s\n", s);
    return 0;
}

void reverse(char s[])
{
    static int i, j;
    char c;

    if (!j)
        j = strlen(s)-1;
    c = s[i];
    s[i++] = s[j];
    s[j--] = c;
    if (i < j)
        reverse(s);
}
