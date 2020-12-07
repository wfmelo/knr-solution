/*
 * Exercise 3-2
 *
 * Write a function escape(s, t) that converts characters like newline and
 * tab into visible escape sequences like \n and \t as it copies the string
 * to to s.  Use a switch.  Write a function for the other direction as
 * well, converting escape sequences into the real characers.
 */
#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char t[], char s[]);

int main()
{
	char s[50] = "\aHello,\n\tWorld! Mistakee\b was \"Extra 'e'\"!\n";
	char t[51];

	printf("Original string: %s\n", s);
	
	escape(s, t);
	printf("Escape string: %s\n", t);

	unescape(t, s);
	printf("Unescape string: %s\n", s);
	return 0;
}

void escape(char s[], char t[])
{
	int i, j;

	i = j = 0;
	while (s[i] != '\0') {
		switch (s[i]) {
			case '\n':
				t[j++] = '\\';
				t[j] = 'n';
				break;
			case '\a':
				t[j++] = '\\';
				t[j] = 'a';
				break;
			case '\t':
				t[j++] = '\\';
				t[j] = 't';
				break;
			case '\b':
				t[j++] = '\\';
				t[j] = 'b';
				break;
			case '\v':
				t[j++] = '\\';
				t[j] = 'v';
				break;
			case '\\':
				t[j++] = '\\';
				t[j] = '\\';
				break;
			case '\"':
				t[j++] = '\\';
				t[j] = '\"';
				break;
			case '\'':
				t[j++] = '\\';
				t[j] = '\'';
				break;
		default:
			t[j] = s[i];
			break;
		}
		++j;
		++i;
	}
	t[j] = s[i];
}

void unescape(char t[], char s[])
{
	int i, j, prev;

	i = j = 0;
	prev = 0;
	while (t[i] != '\0') {
		if (t[i] == '\\') {
			++i;
			switch (t[i]) {
				case 'n':
					s[j] = '\n';
					break;
				case 't':
					s[j] = '\t';
					break;
				case 'v':
					s[j] = '\v';
					break;
				case 'a':
					s[j] = '\a';
					break;
				case 'b':
					s[j] = '\b';
					break;
				case '\\':
					s[j] = '\\';
					break;
				case '\"':
					s[j] = '\"';
					break;
				case '\'':
					s[j] = '\'';
					break;
			}
		}
		++j;
		++i;
	}
	s[j] = t[i];
}
