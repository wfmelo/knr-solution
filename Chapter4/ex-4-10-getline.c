/* Exercise 4-10
 *
 * An alternate organization uses getline to read an entire input line; this
 * makes getch and ungetch unnecessary.  Revise the calculator to use this
 * approach.
 */
#include <stdio.h>
#include <stdlib.h>	/* for declarate atof() */
#include <ctype.h>

#define MAXOP	100	/* maximum size operand or sign */
#define NUMBER	'0'	/* the signal that number found */
#define MAXVAL 100	/* maximum stack depth */
#define MAXLINE 100

int getop(char s[]);
void push(double);
double pop(void);
int getlines(char line[], int lim);

int sp = 0;			/* next free position on the stack */
double val[MAXVAL];	/* operand stack */
char line[MAXLINE];
int ind = 0;

/* reverse polish calculator */
int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			if (type == '\0')
				ind = 0;
			else
				printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

/* push: pushes the number f onto the operand stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error:  stack full, can't push %g\n", f);
}

/* pop: pops and returns the top number from the stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: retrieves the next operand or token of an operation */
int getop(char s[])
{
	int i, c;

	if (!ind)
		if (getlines(line, MAXLINE) == 0)
			return EOF;
	while ((s[0] = c = line[ind++]) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	/* not a number */
	i = 0;
	if (isdigit(c))	/* accumulated floor */
		while (isdigit(s[++i] = c = line[ind++]))
			;
	if (c == '.')	/* accumulated ceiling */
		while (isdigit(s[++i] = c = line[ind++]))
			;
	s[i] = '\0';
	ind--;
	return NUMBER;
}

/*getlines: read string and return length */
int getlines(char line[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		line[i++] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}
