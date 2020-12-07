/*
 * Exercise 3-5
 *
 * Write the function itob(n, s, b) that converts the integer n into a base
 * b character representation in the string s.  In paricular, itob(n, s, 16)
 * formats n as a hexadecimal integer in s.
 */
#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
	char s[100];
	
	itob(500, s, 8);
	printf("%s\n", s);
	return 0;
}

void itob(int n, char s[], int b)
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = (n % b > 9) ? (n % b) - 10 + 'A' : (n % b + '0');
	} while ((n /= b) > 0);	
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* reverse: reverse the order of characters in string s */
void reverse(char s[])
{
	int i, j, c;
	
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
