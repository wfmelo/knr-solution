/* Exercise 5-14
 *
 * Modify the sort program to handle a -r flag, which indicates sorting in
 * reverse (decreasing) order.  Be sure that -r works with -n.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pfnsort.h"

#define MAXLINES 5000    /* maximum number of lines */
#define MAXLEN   1000    /* the maximum length of the input string */

char *lineptr[MAXLINES]; /* pointers to strings */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qqsort(void *lineptr[], int left, int right,
            int (*comp)(void *, void *), int reverse);
int numcmp(char *, char *);
int mygetline(char *line, int lim);

/* sort lines from input stream */
int main(int argc, char *argv[])
{
    int nlines;        /* number of lines read  */
    int numeric = 0;   /* 1 if numeric sort  */
    int reverse = 0;   /* 1 if sorting in descending order */
    int c;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                printf("find: illegeal option %c\n", c);
                argc = 1;
                break;
            }
    if (argc != 0) {
        printf("Usage: pfnsort -n -r pattern\n");
        return 1;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (numeric)
            qqsort((void **) lineptr, 0, nlines-1,
               (int (*)(void*, void*))numcmp , reverse);
        else
            qqsort((void **) lineptr, 0, nlines-1,
               (int (*)(void*, void*))strcmp, reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsort: sorting v[left]...v[right] in ascending order */
void qqsort(void *v[], int left, int right,
            int (*comp)(void *, void *), int reverse)
{
    int i, last;
    void swap(void *v[], int i, int j);

    if (left >= right) /* do nothing if in the array */
        return;        /* less than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i<= right; i++) {
        if (!reverse && (*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
        else if (reverse && (*comp)(v[i], v[left]) > 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    qqsort(v, left, last-1, comp, reverse);
    qqsort(v, last+1, right, comp, reverse);
}

/* readlines: reading lines from an input stream */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* remove line feed character */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: output lines to the output stream */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* numcmp: comparing strings s1 and s2 by numerical values */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int mygetline(char *line, int lim)
{
    char c;
    char *ptr = line;

    while (--lim > 0 && (c=getchar()) != EOF && c !='\n')
        *line++ = c;
    if (c == '\n')
        *line++ = c;
    *line = '\0';
    return line - ptr;
}
