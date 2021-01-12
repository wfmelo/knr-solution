/* Exercise 4-7
 *
 * Write a routine ungets(s) that will push back an entire string onto the
 * input.  Should ungets know about buf and bufp, or should it just use
 * ugetch?
 */
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
void ungets(char s[]);

char buf[BUFSIZE];	/* ungetch buffer */
int bufp = 0;		/* next empty position in buf */

int main()
{
	int c;
	char s[] = "Hello, world!\n";

	ungets(s);
	while ((c=getch()) != EOF)
		putchar(c);
	return 0;
}


int getch(void)	/* character input (possibly returned to the stream) */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)	/* returning a character to the input stream */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* Ungets (s) function returning an entire string of characters into a stream */
void ungets(char s[])
{
	int i;

	i = 0;
	while (s[i] != '\0')
		++i;
	while (i > 0)
		ungetch(s[--i]);
}
