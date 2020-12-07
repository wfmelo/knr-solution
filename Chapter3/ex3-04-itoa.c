/*
 * Exercise 3-4
 *
 * In a two's complement number representation, our version of itoa does not
 * handle the largest negative number, that is, the value of n equal to
 * -(2^(wordsize-1)).  Explain why not,  Modify it to print that value
 * correctly, regardless of the machine on which it runs.
 */
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
	char s[100];

	itoa(-2147483648, s);
	printf("%s\n", s);
	return 0;
}

/* itoa: converts the number n to a character string*/
void itoa(int n, char s[])
{
	int i, sign;
	char c = 0;

	if ((sign = n) < 0)	// write the sign
		n = -n;			// write the sign make the number positive
	if (n < 0) {
		c = 1;
		n = -n - 1;
	}
	i = 0;
	do {	// generate numbers in reverse order
		s[i++] = n % 10 + (c ? '1':'0');	// extract the digit
		c = 0;
	} while ((n /= 10) > 0);	// delete digit
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
		

