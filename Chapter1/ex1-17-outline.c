/* Exercise 1-17.
 Write a program to print all input lines that are longer than 80 
 characters.
 */

#include <stdio.h>
#define MAXLINE 1000    /* maximum string length in a stream */
#define OUTLINE 80      /* line length to output */
#define ROW     100     /* maximum number of lines allowed*/

int mygetline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int len;            /* length of the current line */
    char line[MAXLINE]; /* the currently entered line*/
    char listline[ROW][MAXLINE];  /* list of all lines */
    int i, j;

    i = 0;
    while ((len = mygetline(line, MAXLINE)) > 0) {
        if (len > OUTLINE)
            copy(listline[i], line);
            ++i;
    }
    j = i;
    i = 0;
    printf("\nlines > 80 chars:\n\n");
    while (i <= j) {
        printf("%s", listline[i]);
        ++i;
    }
    return 0;
}

int mygetline(char s[], int lim)
{
    int c, i;
    
    for (i = 0; i < lim-1 && (c=getchar())!=EOF && c!= '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i;
}
