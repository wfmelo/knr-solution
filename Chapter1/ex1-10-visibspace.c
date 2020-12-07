/* Exercise 1-9
Write a program to copy its input to its output, replacing each tab by \t,
and backspace by \b and each backslash by \\.  This makes tabs and
backspaces visible in an unambiguous way.
 */
#include <stdio.h>

int main() 
{
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\t')
			c = '\b';
		else if (c == '/')
			c = '\\';
		putchar(c);
	}
}
