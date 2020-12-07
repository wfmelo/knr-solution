/*
Write a program to remove all comments from a C program.  Don't forget to
handle quoted strings and character constants properly.  C comments do not
nest.
*/
#include <stdio.h>
#define MAXLINE	1000

int main()
{
	int c, i, ch;
	int double_quote;
	int in_comment;
	char listing[MAXLINE];
	
	double_quote = 0;
	in_comment = i = 0;
	while ((c = getchar()) != EOF) {
		if (c == '"') {
			if (double_quote == 0)
				double_quote = 1;
			else
				double_quote = 0;
			listing[i] = c;
			i += 1;
		}
		else
			if (c == '/') {
				if ((ch=getchar()) == '*') {
					in_comment = 1;
					while (in_comment == 1) {
						ch = getchar();
						if (ch == '*')
							if (getchar() == '/')
								in_comment = 0;
					}
				}
				else if (ch == '/') {
					in_comment = 1;
					while (in_comment == 1) {
						ch = getchar();
						if (ch == '\n') {
							in_comment = 0;
							listing[i] = ch;
							i += 1;
						}
					}
				}
				else {
					listing[i] = c;
					i += 1;
					listing[i] = ch;
					i += 1;
				}
			}
			else {
				listing[i] = c;
				i += 1;
			}
		}
	listing[i] = '\0';
	if (listing > 0) {
		printf("\n----------CODE WITHOUT COMMENTS----------\n\n");
		printf("%s", listing);
	}
	return 0;
}
