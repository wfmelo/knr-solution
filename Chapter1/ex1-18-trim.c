/* Exercise 1-18.
 Write a program to remove trailing blanks and tabs from each line of input,
 and to delete entirely blank lines.
 */
#include <stdio.h>
#define MAXLINE 1000    /* maximum string length in a stream */

int mgetline(char line[], int maxline );

int main()
{
    int len;
    char line[MAXLINE];
    int lstchr;

    while ((len = mgetline(line, MAXLINE)) > 0) {
        lstchr = 2;
        while (line[len-lstchr] == ' ' || line[len-lstchr] == '\t') {
            line[len-lstchr] = '\b';
            ++lstchr;
        }
        if (line > 0 && len-lstchr > 0)
            printf("%s", line);
    }
    return 0;
}

int mgetline(char sym[], int lim)
{
    int c, i;

    for (i = 0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        sym[i] = c;
    if (c == '\n') {
        sym[i] = c;
        ++i;
    }
    sym[i] = '\0';
    return i;
}
