/* Exercise 4-2
 *
 * Extend atof to handle scientific notation of the form
 * 
 * 	123.45e-6
 * 
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent.
 */
#include <stdio.h>
#include <ctype.h>
#define MAXLINE	100

int main()
{
	double atof(char[]);
	char line[MAXLINE];
	int getlines(char line[], int max);

	while (getlines(line, MAXLINE) > 0)
		printf("\t%g\n", atof(line));
	return 0;
}

/* atof: conversion string s in double */
double atof(char s[])
{
	double val, power, res, pow;
	int i, sign, j;

	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for(val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}	
	res = sign * val / power;
	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		sign = (s[i] == '-') ? -1 : 1;
		if (s[i] == '+' || s[i] == '-')
			i++;
		for(pow = 0.0; isdigit(s[i]); i++)
			pow = 10.0 * pow + (s[i] - '0');
		for (j = 0; j < pow; j++)
			if (sign != -1)
				res *= 10;
			else
				res /= 10;
	}
	return res;
}

// getline: read string s, and return length
int getlines(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
