#include <stdio.h>

/* Verify that the expression getchar() != EOF is 0 or 1. */

int main()
{
	int c;
	
	c = getchar() != EOF;
	printf("End of file : EOF?(0 - yes, 1 - no) - %d\n", c);
}
