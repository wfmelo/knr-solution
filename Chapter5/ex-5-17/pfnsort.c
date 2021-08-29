/* Exercise 5-17
 *
 * Add a field-handling capability, so sorting may be done on fields within
 * lines, each field sorted according to an independent set of options.  (The
 * index for this book was sorted with -df for the index category and -n for the
 * page numbers.)
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pfnsort.h"

#define MAXLINES 5000    /* maximum number of lines */
#define MAXLEN   1000    /* the maximum length of the input string */
#define NUMERIC  1       /* 1, if numeric sort */
#define REVERSE  2       /* 1, if sorting in descending order */
#define FOLD     4       /* case insensitive */
#define DIR      8       /* catalog type ordering */

char *lineptr[MAXLINES]; /* pointers to strings */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int rev);
void quicksort(void *lineptr[], int left, int right,
            int (*comp)(void *, void *));
int numcmp(char *, char *);
int mycmp(char *, char *);
int mygetline(char *line, int lim);

static char option = 0;

int pos1 = 0;
int pos2 = 0;

/* sort lines from input stream */
int main(int argc, char *argv[])
{
    int nlines;        /* number of lines read */
    int c;

    while (--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+'))
        if (c == '-' && !isdigit(*(argv[0] + 1))) {
            while (c = *++argv[0])
                switch (c) {
                case 'n':
                    option |= NUMERIC;
                    break;
                case 'r':
                    option |= REVERSE;
                    break;
                case 'f':
                    option |= FOLD;
                    break;
                case 'd':
                    option |= DIR;
                    break;
                default:
                    printf("Illegeal option %c\n", c);
                    argc = 1;
                    break;
                }
        }
        else if (c == '+')
            pos1 = atoi(argv[0]+1);
        else if (c == '-')
            pos2 = atoi(argv[0]+1);
    printf("pos1: %d\npos2: %d\n", pos1, pos2);
    if (argc != 0) {
        printf("Usage: pfnsort -n -r -f -d [+start] [-end] pattern\n");
        return 1;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (option & NUMERIC)
            quicksort((void **) lineptr, 0, nlines-1,
               (int (*)(void*, void*))numcmp);
        else
            quicksort((void **) lineptr, 0, nlines-1,
               (int (*)(void*, void*))mycmp);
        writelines(lineptr, nlines, option & REVERSE);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsort: sorting v[left]...v[right] in ascending order */
void quicksort(void *v[], int left, int right,
            int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int i, int j);

    if (left >= right) /* do nothing if in the array */
        return;        /* less than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i<= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last-1, comp);
    quicksort(v, last+1, right, comp);
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
void writelines(char *lineptr[], int nlines, int rev)
{
    int i;
    
    if (rev)  /* print in descending order */
        for (i = nlines-1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    else
        while (nlines-- > 0)
            printf("%s\n", *lineptr++);
}

/* numcmp: comparing strings s1 and s2 by numerical values */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    int i;
    char str[1+pos2-pos1];

    if (pos2 > 0 && pos2-pos1 > 0) {
        for (i = 0; pos1 + i < pos2; i++, s1++)
            str[i] = *s1;
        str[i] = '\0';
        v1 = atof(str);
        for (i = 0; pos1 + i < pos2; i++, s2++)
            str[i] = *s2;
        str[i] = '\0';
        v2 = atof(str);
    } else {
        v1 = atof(s1);
        v2 = atof(s2);
    }
    printf("v1 = %f v2 = %f\n", v1, v2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int mycmp(char *s1, char *s2)
{
    char a, b;
    int dir = (option & DIR) ? 1 : 0;
    int fold = (option & FOLD) ? 1 : 0;
    char str1[1+pos2-pos1], str2[1+pos2-pos1];
    char *p1, *p2;
    int i;

    if (pos2 > 0 && pos1 > 0) {
        for (i = 0; pos1 + i < pos2; i++, s1++)
            str1[i] = *s1;
        str1[i] = '\0';
        for (i = 0; pos1 + i < pos2; i++, s2++)
            str2[i] = *s2;
        str2[i] = '\0';
        p1 = str1;
        p2 = str2;
    } else {
        p1 = s1;
        p2 = s2;
    }
    do {
        if (dir) {
            while (!isalnum(*p1) && *p1 != ' ' && *p1 != '\0')
                *p1++;
            while (!isalnum(*p2) && *p2 != ' ' && *p2 != '\0')
                *p2++;
        }
        a = fold ? tolower(*p1) : *p1;
        *++p1;
        b = fold ? tolower(*p2) : *p2;
        *++p2;
        if (a == b && a == '\0')
            return 0;
    } while (a == b);
    return a - b;
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
