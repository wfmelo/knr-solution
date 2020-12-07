/* Exercise 1-9
 * Write a program to copy its input to its output, replacing each string of
 * one or more blanks by a single blank.
 */
#include <stdio.h>

int main()
{
	int c, ns;
	
	ns = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++ns;
		else
			ns = 0;
		if (ns <= 1)
			putchar(c);
	}
}
