/*
Write a program to remove all comments from a C program.  Don't forget to
handle quoted strings and character constants properly.  C comments do not
nest.
*/
#include <stdio.h>
#define MAXCHAR	 10000		/* permissible number of chars in the program listing */
#define MAX		 1000		/* allowed number of characters per line */
#define IN		 1			/* in the comment */
#define OUT		 0			/* outside comments */
#define INLN	 2			/* in one line */

int mygetline(char line[], int limit);

int main()
{
	int c, i, p, k;
	int comment_in_line;
	int len;	
	int state;				/* state in comment or not */
	int non_emp_char;
	int double_quote;
 	char listing[MAXCHAR];	/* листинг программы без коментариев */
	char line[MAX]; 	/* program listing without comments */

	len = p = k = i = 0;
	double_quote = 0;
	state = OUT;
	non_emp_char = 0;
	comment_in_line = 0;
	while((len = mygetline(line, MAX)) > 0) {
		p = i = 0;
		while (i < len) {
			if (state == OUT)
				if (line[i] == '"'  && double_quote == 0 && line[i-1] != '\\')
					double_quote = 1;
				else if (line[i] == '"' && double_quote == 1 && line[i-1] != '\\')
					double_quote = 0;
			if (double_quote == 0) {
				if (line[i] == '/' && line[i+1] == '*') {
					comment_in_line = 1;
					state = IN;
					i = i + 2;
				}
				else if (line[i] == '*' && line[i+1] == '/') {
					comment_in_line = 1;
					state = OUT;
					i = i + 2;
				}
				else if (line[i] == '/' && line[i+1] == '/') {
					comment_in_line = 1;
					state = INLN;
					i = i + 2;
				}
				else if (line[i] == '\n' && state == INLN)
					state = OUT;
			}
			if (state == OUT || double_quote == 1) {
				if (line[i] != '\t' && line[i] != ' ' && line[i] != '\n')
					++non_emp_char;
				line[p] = line[i];
				++p;
			}
			++i;
		}
		if ((state == OUT || double_quote == 1) &&
			(non_emp_char != 0 || comment_in_line == 0)) {
			for (int j = 0; j < p; ++j) {
				listing[k] = line[j];
				++k;
			}
			non_emp_char = 0;
			comment_in_line = 0;
		}
		else if (state == IN && non_emp_char != 0 && comment_in_line != 0) {
			for (int j = 0; j < p; ++j) {
				listing[k] = line[j];
				++k;
			}
		}
	}
	if (listing > 0)
		printf("\n----------CODE WITHOUT COMMENTS----------\n\n");
		printf("%s", listing);
	return 0;
}

int mygetline(char line[], int lim)
{
	int c, i;
	
	for (i = 0; i<lim && (c=getchar())!=EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}


