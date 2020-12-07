/* Exercise 1-12
Write a program that prints its input one word per line.
*/
#include <stdio.h>

#define IN  1	/* inside a wordа */
#define OUT 0	/* outside the word */


int main()
{
	int c, state;

	state = OUT;
	while ((c = getchar()) != EOF)
		if (c == ' ' || c == '\n' || c == '\t') { 
			if (state == IN)
				putchar('\n');
			state = OUT;
		}
		else {
			putchar(c);
			state = IN;
		}
}
