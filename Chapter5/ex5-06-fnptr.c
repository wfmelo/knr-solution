/*
 * Exercise 5-5.
 *
 * Rewrite appropriate programs from earlier chapters and exercises with
 * pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and
 * 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000

int mygetline(char *s, int lim);
int atoi(char *s);
char *itoa(int n, char *s);
void reverse(char *s);
int strindex(char *s, char *t);
int getop(char *s);
double atof(char *s);

int main()
{
    char str[MAXLINE];
    char s[32];
    int n;
    double nf;
    
    printf("Length string: %d\n", mygetline(str, MAXLINE));
    printf("String: %s", str);
    n = atoi(str);
    printf("atoi: %d\n", n);
    printf("itoa: %s\n", itoa(n, s));
    nf = atof("321.25");
    printf("atof: %g\n", nf);
    printf("strindex: %d\n", strindex("Hello, world", "world"));
    n = getop(s);
    printf("getop: n = %d, %s\n", n, s) ;
    return 0;
}

/* mygetline: read line in s return length */
int mygetline(char *s, int lim)
{
    int c;
    char *ps = s;
    
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - ps;
}

/* atoi: converts line s in integer type int */
int atoi(char *s)
{
    int sign, n;

    while (isspace(*s))
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (n = 0; isdigit(*s); s++)
        n = n * 10 + (*s - '0');
    return n * sign;
}
/* itoa: convernts number int in string */
char *itoa(int n, char *s)
{
    int sign;
    char *ptr = s;

    if ((sign = n) < 0)
        n = -n;
    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(ptr);
    return ptr;
}
/* reverse: reverse the string */
void reverse(char *s)
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = *(s+i);
        *(s+i) = *(s+j);
        *(s+j) = c;
    }
}
/* strindex: return index string t in s, -1 in the absence */
int strindex(char *s, char *t)
{
    char *ps = s;
    char *pt, *pk;
    
    for ( ; *s != '\0'; s++) {
        for (pt = t , pk = s; *pk != '\0' && *pk == *pt; pt++, pk++)
            ;
        if (pk > pt && *pk == '\0')
            return s - ps;
    }
    return -1;
}

/* getop: retrieves the next operand or token of an operation */
int getop(char *s)
{
    int c;

    while((*s = c = getchar()) == ' ' && c == '\n')
        ;
    *(s+1) = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    if (isdigit(c)) /* accumulation of int part */
        while (isdigit(*(++s) = c = getchar()))
            ;
    if (c == '.')    /* fractional accumulation */
        while (isdigit(*(++s) = c = getchar()))
            ;
    *s = '\0';
    return '0';
}

double atof(char *s)
{
    double val, power;
    int sign;

    while(isspace(*s))
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (val = 0.0; isdigit(*s); s++)
        val = 10.0 * val + (*s - '0');
    if (*s == '.')
        s++;
    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }
    return sign * (val / power);
}
