/*
 * Exercise 2-4
 *
 * Write an alternate version squeeze (s1, s2) that deletes each character 
 * in s1 that matches any character in the string s2.
 */
#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main()
{
	char s1[] = "Write an alternate version of squeeze(s1,s2)"
				"\nthat deletes each character in the string s1"
	 			"\nthat matches any character in the string s2.";
	char s2[] = "io";

	squeeze(s1, s2);
	printf("%s", s1);
	return 0;
}

void squeeze(char s1[], char s2[])
{
	int i, j, k;

	for (k = 0; s2[k] != '\0'; k++) {
		for (i = j = 0; s1[i] != '\0'; i++)
			if (s1[i] != s2[k])
				s1[j++] = s1[i];
		s1[j] = '\0';
	}
}
