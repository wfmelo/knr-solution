/*
 * Exercise 5-7.
 *
 * Rewrite readlines to store lines in an array supplied by main rather than
 * calling alloc to maintain storage.  How much faster is the program?
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 5000    /* the maximum number of lines to sort */
#define MAXLEN 1000     /* maximum length input line */
#define ALLOCSIZE 10000 /* buffer memory for array strings */

char *lineptr[MAXLINE];    /* point to strings */

int readlines(char *lineptr[], int nlines, char *buffer);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int mygetline(char *, int);

/* sorting the lines of the input stream  */
int main(void)
{
    int nlines;    /* number of entered lines */
    char buffer[ALLOCSIZE]; /* array string */

    if ((nlines = readlines(lineptr, MAXLINE, buffer)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read line from input stream */
int readlines(char *lineptr[], int maxlines, char *buffer)
{
    int len, nlines, size;
    char *p = buffer, line[MAXLEN];

    nlines = size = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (size += len) > ALLOCSIZE)
            return -1;
        else {
            line[len-1] = '\0'; /* remove line feed character */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p = &buffer[size];
        }
    return nlines;
}

/* writelines: output lines to the output stream  */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
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

/* qsort: sorting v[left]...v[right] in ascending order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    
    if (left >= right) /* do nothing if the array */
        return ;       /* has less than two elements */
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: swap position v[i] in v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
