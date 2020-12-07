/* Exercise 1-19.
Write a function reverse(s) that reverses the character string s.  Use it to
write a program that reverses its input a line at a time.
*/

#include <stdio.h>
#define MAXLINE 1000    /* maximum number of characters in a line */

int mgetline(char line[], int maxline);
void reverse(char line[], int len);  

/* recursive line output */
int main()
{
    int len;            /* length of the current line */
    char line[MAXLINE];     /* the currently entered line */
    char revline[MAXLINE];  /* reversed line */

    while ((len = mgetline(line, MAXLINE)) > 0) {
        if (len > 0)
            reverse(line, len);
            printf("%s", line);
            
    }
    return 0;
}
/* mgetline: reads a string in sym returns its lengthу */
int mgetline(char sym[], int lim)
{
    int i, c;
    for (i = 0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        sym[i] = c;
    if (c == '\n') {
        sym[i] = c;
        ++i;
    }
    sym[i] = '\0';
    return i;
}

/* reverse: copies the line line [] in reverse order */
void reverse(char line[], int len)
{
    int i = 0;
    char tmp;
    
    len = len - 2;
    while ((len+1)/2 != i) {
        tmp = line[len-i];
        line[len-i] = line[i];
        line[i] = tmp;
        ++i;
    }
}
