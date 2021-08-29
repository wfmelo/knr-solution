/*
 * Exercise 7-4.
 *
 * Write a private version of scanf analogous to minprintf from the previous
 * section.
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

void minscanf(char *fmt, ...);

int main(void)
{
    int ival, ival2;
    double dval;
    char sval[20];

    printf("Enter string: ");
    minscanf("%s", sval);
    printf("Output: %s\n", sval);
    printf("Enter two int: ");
    minscanf("%d %d", &ival, &ival2);
    printf("Output: %d %d\n", ival, ival2);
    printf("Enter int: ");
    minscanf("%d", &ival);
    printf("Output: %d\n", ival);
    printf("Enter double: ");
    minscanf("%f", &dval);
    printf("Output: %lf\n", dval);
    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int *ival, c;
    double *dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%')
            continue;
        else if (*p == '\0')
            break;
        switch (*++p) {
        case 'd':
            ival = va_arg(ap, int *);
            scanf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double *);
            scanf("%lf", dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            while (isalpha(c = getchar()) != EOF && !isspace(c))
                *sval++ = c;
            *sval = '\0';
            break;
        default:
            return;
        }
    }
}
