/*
 * Exercise 7-1
 *
 * Write a program that converts upper case to lower or lower case to upper,
 * depending on the name it is invoked with, as found ing argv[0].
 */

/*
 * Converts to lower or upper depending on whether the name contains an 'l' or a
 * 'u' first.  If the name contains neither 'l' nor 'u' the input is unchanged.
 */

#include <stdio.h>
#include <ctype.h>

#define UPPER 1
#define LOWER 0

int main(int argc, char **argv)
{
    int c, regist = LOWER;

    for ( ; *argv[0] != '\0'; *++argv[0])
        if (!isalpha(*argv[0]))
            ;
        else if (isupper(*argv[0]))
            regist = UPPER;
        else {
            regist = LOWER;
            break;
        }
    while ((c = getchar()) != EOF)
        if (regist)
            putchar(toupper(c));
        else
            putchar(tolower(c));
    return 0;
}
