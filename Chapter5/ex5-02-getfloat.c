/*
 * Exercise 5-2
 *
 * Write getfloat, the floating-point analog of getint.  What type does
 * getfloat return as its fucntion value?
 */
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
#define SIZE    100

float getfloat(float *pn);
int getch(void);
void ungetch(int);

char buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;         /* next empty position in buf */

int main(void)
{
    int n, array[SIZE];
    float x;
    /*
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
        printf("\n");*/
    getfloat(&x);
    printf("%g\n", x);
    return 0;
}

float getfloat(float *pn)
{
    int c, sign;
    float frac = 0;
    int power = 1;
    
    while (isspace(c = getch()))    /* skip spaces */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);    /* not number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    if (c == '.') {
        while(isdigit(c = getch())) {
            frac  =  10 * frac + (c - '0');
            power *= 10;
        }
        frac = frac / power;
        *pn = *pn + frac;
    }
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}
// 5.23 -> 5 + 0.23 
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
