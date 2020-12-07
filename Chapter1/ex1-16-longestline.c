/* Exercise 1-16. 
Revise the main routine of the longest-line program so it  will correctly 
print the length of arbitrarily long input lines, and as much as possible of
the text.
*/
#include <stdio.h>
#define MAXLINE 1000    /* maximum string length in a stream */

int mygetline(char line[], int maxline);
void copy(char to[], char from[]);

/* output the longest line in the stream */
int main()
{
    int len;                /* length of the current line */ 
    int max;                /* current maximum length */
    char line[MAXLINE];     /* currently entered lineа */
    char longest[MAXLINE];  /* longest line entered */
    char c;

    max = 0;
    while ((len = mygetline(line, MAXLINE)) > 0) {
        if (line[len - 1] != '\n') {
            while ((c=getchar()) != EOF && c != '\n')
                len++;
        }
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0)    /* line not empty*/
        printf("len = %d; line: %s", max, longest);
    return 0;
}

/* getline: reads a string into s, returns its length */
int mygetline(char s[], int lim)
{
    int c, i;

    for (i = 0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copies the string 'from' to 'to'; the length to is considered sufficient */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
