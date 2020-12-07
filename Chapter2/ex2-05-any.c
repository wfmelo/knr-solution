/*
 * Exercise 2-5
 *
 * Write the function any(s1, s2), which returns the first location in the
 * string s1 wher any character from the string s2 occurs, or -1 if s1
 * contains no characters from s2.  (The standard library function strpbrk
 * does the same job but returns a pointer to the locations.)
 */
#include <stdio.h>

int any(char s[], char t[]);

int main()
{
	char s[] = "Custom firmwarx";
	char t[] = "nxrxfs";

	printf("%d", any(s, t));
	
	return 0;
}

int any(char s[], char t[])
{
	int i, j;

	i = j = 0;
	while (s[i] != '\0') {
		while(t[j++] != '\0') {
			if (s[i] == t[j])
				return i;
		}
		++i;
		j = 0;
	}
	return -1;
}
