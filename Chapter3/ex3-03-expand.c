/*
 * Exercise 3-3
 *
 * Write a function expand(s1, s2) that expands shorthand notations like a-z
 * in the string s1 into the equivalent complete list abc...xyz in s2.
 * Allow for letters of either case and digits, and be prepared to handle
 * cases like a-b-c and a-z0-9 and -a-z.  Arrange that a leading or trailing
 *  - is taken literally.
 */
#include <stdio.h>

void expand(char s1[], char s2[]);
int isalpha(int c);

int main()
{
	char s[1000];

	expand("-a-z testing a-f a-b-c A-Za-z0-9 testing 5-9 a-d-f 1-3-6-9", s);
	printf("%s\n", s);
	return 0;
}

void expand(char s1[], char s2[])
{
	int i, j, k;

	k = 0;
	for(i = 0; s1[i] != '\0'; i++) {
		if (isalpha(s1[i]) && s1[i+1] == '-' && isalpha(s1[i+2])
			&& (s1[i+2] - s1[i] > 1)) {
			for (j = s1[i]; j < s1[i+2]; j++) {
				s2[k++] = j;
			}
			i++;
		}
		else
			s2[k++] = s1[i];
	}
	s2[k] = '\0';
}

int isalpha(int c)
{
	return ((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'));
}
