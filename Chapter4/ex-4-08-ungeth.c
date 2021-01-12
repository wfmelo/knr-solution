/* Exercise 4-8
 *
 * Suppose that there will never be more than one character of pushback.
 * Modify getch and ungetch accordingly.
 */
#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int buf;	/* ungetch  buffer */

int main()
{
	int c;
	
	c = getch();
	ungetch(c);
	ungetch(c);
	return 0;
}


int getch(void)	/* input character (possibly returned to the stream)*/
{
	int c;
	
	if (buf != 0)
		c = buf;
	else
		c = getchar();
	buf = 0;
	return c;
}

void ungetch(int c)	/* returning a character to the input stream */
{
	if (buf !=  0)
		printf("ungetch: too many characters\n");
	else
		buf = c;
}
