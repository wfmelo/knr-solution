/*
 * Exercise 2.2
 *
 * Write a loop equivalent to the for loop above without using && or ||.
 */
#include <stdio.h>
#define MAXLINE 1000

int mygetline(char s[], int maxline);

int main()
{
	int len;
	char line[MAXLINE];
	
	len = mygetline(line, MAXLINE);
	printf("%d", len);
	return 0;
}

int mygetline(char s[], int lim)
{
	int i, c;
	
	while (i < lim - 1) {
		if ((c=getchar()) != '\n') {
			if (c != EOF) {
				s[i] = c;
			}
		}
		i++;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
