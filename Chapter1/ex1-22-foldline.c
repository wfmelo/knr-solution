/* Exercise 1-22.
Write a program to "fold" long input lines into two or more shorter lines
after the last non-blank character that occurs before the n-th column of
input. Make sure your program does something intelligent with very long
lines, and if there are no blanks or tabs before the specified column.
*/
#include <stdio.h>
#define MAXLINE 1000	/* maximum line length of the input stream */
#define LIMLINE 30		/* limit length of one line */		

int mygetline(char line[], int len);
void splitline(char line[], int maxlen);


int main()
{
    int len;			/* length of the current line */
    char line[MAXLINE]; /* character string input stream */
	
	while ((len = mygetline(line, MAXLINE)) > 0) {
		if (len > LIMLINE)
			splitline(line, len);
		else 
			printf("%s", line);
	}
	return 0;
}

/* mygetline: creates a character string and returns its length*/
int mygetline(char line[], int lim)
{
	int i, c;

	for (i = 0; i<lim-1 && ((c=getchar())!=EOF) && c!='\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

void splitline(char line[], int len)
{
	int cn;			/* the number of characters in the current line */	
	int empt;		/* index of the last blank character */
	int lastemp;	/* last empty character (Boolean) */
	int start;		/* newline character index */
	int end;		/* end-of-line character index */
	
	cn = lastemp = empt = 0;
	start = end = 0;
	for (int i = 0; i < len; ++i) {
		if (cn >= LIMLINE || line[i] =='\n') {
			end = (start + empt) - 1;	// end of line without blank character
			if (line[i] == '\n') {
				end = start + cn;
			}
			if (empt == 0 && cn >= LIMLINE) {
				end = LIMLINE;
				cn = 0;
			}
			for (int j = start; j < end; ++j)
				putchar(line[j]);
			putchar('\n');
			start = start + empt;
			cn = cn - empt;
		}
		if (line[i] == ' ' || line[i] == '\t') {
			++cn;
			if (lastemp != 1)
				empt = cn;		// Remember the position after its empty
			lastemp = 1;
		}
		else {
			++cn;
			lastemp = 0;
		}
	}
}
