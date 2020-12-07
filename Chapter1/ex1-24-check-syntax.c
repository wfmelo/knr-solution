/*
Write a program to check a C program for rudimentary syntax errors like
unbalanced parenthesis, brackets and braces.  Don't forget about quotes,
both single and double, escape sequences and comments.  (This program is
hard if you do it in full generality.)
*/
#include <stdio.h>
#define MAX		1000
#define CODE	0
#define COMMENT	1
#define SQUOTE	2
#define DQUOTE	3

int check_bracket(int bracket);
int check_state(int c);


int main()
{
	int c, state, error;
	int line, index, column, count;
	int prev, prev_prev;
	char symbol[MAX];

	line = 1;
	state = CODE;
	error = column = index = prev = prev_prev = count = 0;
	while ((c=getchar()) != EOF) {
		if (!error)
			++column;
		if (c == '\n' && !error) {
			++line;
			column = 0;
		}
		else if (state == CODE && !error) {
			state = check_state(c);
			count = 0;
			if (c == '{' || c == '[' || c == '(') {
				symbol[index] = c;
				++index;
			}
			else if (c == '}' || c == ']' || c == ')') {
				if (symbol[index - 1] == check_bracket(c))
					--index;
				else
					error = 1;
			}
		}
		else if (state == SQUOTE) {
			if (c == '\''  && (prev != '\\' || prev_prev == '\\')
				&& count!=0) {
				state = CODE;
			}
			else if ((c == '}' || c == ']' || c == ')' ||
					  c == '{' || c == '[' || c == '(') && count != 0)
				error = 1;
			count = 1;
		}
		else if (state == DQUOTE) {
			if (c == '"'  && (prev != '\\' || prev_prev == '\\')
				&& count != 0) {
				state = CODE;
			}
			else if ((c == '}' || c == ']' || c == ')' ||
					  c == '{' || c == '[' || c == '(') && count != 0)
				error = 1;
			count = 1;
		}
		else if (state == COMMENT) {
			if (prev == '*' && c == '/')
				state = CODE;
		}
		prev_prev = prev;
		prev = c;	
	}
	/* Error message display */
	if (index != 0 && state == CODE) {
		printf("\n%d:%d: error: unbalanced bracket '%c'\n", line, column,
			   check_bracket(symbol[index-1]));
	}
	else if (state == COMMENT)
		printf("\n%d:%d: error: unterminated comment\n", line, column);
	else if (state == DQUOTE && error)
		printf("\n%d:%d: error: unbalnaced double quote\n", line, column);
	else if (state == SQUOTE && error)
		printf("\n%d:%d: error: unbalnaced single quote\n", line, column);
	else
		printf("\nALL BALANCED\n");
	printf("\n%d %d %d", index, state, error);
	return 0;
}

/* Matching a closing parenthesis and an opening */
int check_bracket(int bracket)
{
	if (bracket == '}')
		return '{';
	else if (bracket == ']')
		return '[';
	else if (bracket == ')')
		return '(';
	else if (bracket == '{')
		return '}';
	else if (bracket == '[')
		return ']';
	else if (bracket == '(')
		return ')';
	else
		return 0;
}

/* Choosing a parser mode */
int check_state(int c)
{
	if (c == '\'')
		return SQUOTE;
	else if (c == '"')
		return DQUOTE;
	else if (c == '/')
		return COMMENT;
	else
		return CODE;
}
