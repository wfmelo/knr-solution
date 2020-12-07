/*
 * Exercise 3-6
 *
 * Write a version of itoa that accepts three arguments instead of two.  The
 * third argument is a minimum field width; the converted number must be
 * padded with blanks on the left if necessary to make it wide enought.
 */
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int w);
void reverse(char s[]);

int main()
{
	char s[100];
	
	itoa(-12, s, 10);
	printf("%s\n", s);
	return 0;
}

void itoa(int n, char s[], int w)
{
	int i, sign, j, k;

	if ((sign = n) < 0)
		n = - n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	while (i < w)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}

/* reverse: reverse the order of characters in string */
void reverse(char s[])
{
	int i, j, c;
	
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
