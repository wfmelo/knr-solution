/* Exercise 1-21.
Write a program entab that replaces strings of blanks by the minimum number
of tabs and blanks to achieve the same spacing.  Use the same tab stops as
for detab.  When either a tab or a single blank would suffice to reach a tab
stop, which should be given preferene?
*/
#include <stdio.h>
#define TAB     8
#define MAXLINE 1000

int mgetline(char line[], int lim);

int main()
{
    int len;            /* string length */
    int count;          /* count of the number of spaces in the line */
    char line[MAXLINE]; /* character string */
    
    count = 0;
    while ((len = mgetline(line, MAXLINE)) > 0)
        for(int i = 0; i < len; ++i) {
            if (line[i] == ' ') {
                ++count;
                if (count == TAB) {
                    putchar('\t');
                    count = 0;
                }
            }
            else {
                if (count > 0 && count < 8)
                    for (int j = 0; j < count; ++j)
                        putchar(' ');
                count = 0;
                putchar(line[i]);
            }
        }
}

/* mgetline: read string and returning its length. */
int mgetline(char line[], int lim)
{
    int c, i;

    for (i = 0; i<lim-1 && ((c=getchar())!=EOF) && c!='\n'; ++i)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return 0;
}
