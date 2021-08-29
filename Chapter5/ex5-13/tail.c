/*
 * Exercise 5-13
 *
 * Write the program tail, which prints the last n lines of its input.  By
 * default, n is 10, let us say, but it can be changed by an optional
 * argument, so that
 *
 * 	tail -n
 *
 * prints the last n lines.  The program should behave rationally no matter
 * how unreasonable the input or the value of n.  Write the program so it
 * makes the best use of available storage; lines should be stored as in the
 * sorting program of Section 5.6, not in a two-dimensional array of fixed
 * size.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tail.h"

#define MAXLEN   1000   /* maximum line length */
#define MAXLINES 100    /* maximum number of lines to display */
#define DEFLIN   10     /* number of lines to display - default value */

int mygetline(char *line, int lim);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

char *lineptr[MAXLINES];

int main(int argc, char *argv[])
{
    int n = DEFLIN;    /* number of lines per output */
    int nlines;
    
    if (argc == 2 && (*++argv)[0] == '-')
        n = atoi(++argv[0]);
    else if (argc == 1)
        n = DEFLIN;
    else {
        printf("call: tail [-n]\n");
        return 1;
    }
    printf("%d\n", n);

    if (n < 1 || n > MAXLINES)    /* incorrect value */
        n = MAXLINES;
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (nlines < n)
            writelines(lineptr, nlines);    /* print all available lines */
        else {
            printf("-------------------------------\n");
            writelines(lineptr + (nlines - n), n);    /* print a given number of lines к */
            printf("-------------------------------\n");
        }
        return 0;
    } else {
        printf("error: input too big\n");
        return 1;
    }
}

int readlines(char *lineptr[], int maxlines)
{
     int len, nlines;
     char *p,  line[MAXLEN];

     nlines = 0;
     while ((len = mygetline(line, MAXLEN)) > 0) {
         if (nlines >= maxlines || (p = alloc(len)) == NULL)
             return -1;    // error;
         else {
             line[len-1] = '\0';    /* remove line feed character  */
             strcpy(p, line);
             lineptr[nlines++] = p;
         }
     }
     return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

int mygetline(char *line, int lim)
{
    int c;
    char *p = line;

    while (--lim>0 && (c = getchar())!=EOF && c!='\n')
        *line++ = c;
    if (c == '\n')
        *line++ = c;
    *line = '\0';
    return line - p;
}
