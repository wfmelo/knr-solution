/*
 * Exercise 5-1
 *
 * As written, getint treats a + or - not followed by a digit as a valid
 * representation of zero.  Fix it to push such a character back on the
 * input.
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
#define SIZE    100

int getint(int *pn);
int getch(void);
void ungetch(int);

char buf[BUFSIZE];    /* buffer ungetch */
int bufp = 0;         /* next empy position in buf */

int main(void)
{
    int n, array[SIZE], x;
    /*
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
        printf("\n");*/
    getint(&x);
    printf("%d\n", x);
    getint(&x);
    printf("%d\n", x);
    return 0;
}
/* Function getint performs unformatted conversion
 * input stream by breaking the character string into integers
 * and entering one number at a time. */
/* getint: read int number
 *         from input stream in *pn */
int getint(int *pn)
{
    int c, sign, d;

    while (isspace(c = getch()))    /* skip spaces */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);    /* not number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        d = c;
        c = getch();
        if (!isdigit(c = getch())) {
            if (c != EOF)
                ungetch(c);
            ungetch(d);
            return d;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
