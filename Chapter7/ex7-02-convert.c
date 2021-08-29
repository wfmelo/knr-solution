/* 
 * Exercise 7-2
 *
 * Write a program that will print arbitrary input in a sensible way.  as a
 * minimum, it should print non-graphic characters in octal or hexadecimal
 * according to local custom, and break long text lines.
 */
#include <stdio.h>
#include <ctype.h>

#define SIZE 50
#define LINELEN 76
#define TAB 6
#define FORMAT "<0x%02x>"
#define BUFFSIZE 100

int isprintable(int);
int getch(void);
void ungetch(int c);

char buf[BUFFSIZE];
int bufp = 0;

int main(void)
{
    int c, i, j;
    int pos = 0;
    int n = TAB;
    int inword = 0;
    char word[SIZE];

    while ((c = getch()) != EOF) {
        if (n == 0 || c == '\n')
             n = TAB;
        --n;
        if (isprintable(c)) {
            if (c == '\t') {
                for (i = 0; i < n; ++i)
                    putchar(' ');
                pos += 4;
                n = TAB;
                continue;
            } else if (c == '\n' || pos == LINELEN) {
                if (c != '\n')
                    putchar('\n');
                putchar(c);
                pos = 0;
                continue;
            } else
                putchar(c);
        } else
            printf(FORMAT, c);
        pos++;
            
    }
    
    return 0;
}

int isprintable(int c)
{
    if ((0x20 <= c && c <= 0x7e) || (0x08 <= c && c <= 0x0c))
        return 1;
    return 0;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
