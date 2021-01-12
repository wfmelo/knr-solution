/* Exercise 4-9
 *
 * Our getch and ugetch do not handle a pushed-back EOF correctly.  Decide
 * what their properties ought to be if an EOF is pushed back, then 
 * implement your design.
 */
#include <stdio.h>
#include <stdlib.h>	/* for declarate atof() */
#include <ctype.h>

#define MAXOP	100	/* maximum size operand or sign */
#define NUMBER	'0'	/* the signal that number found */
#define MAXVAL 100	/* maximum stack depth */
#define BUFSIZE 100

int getop(char s[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0;			/* next free position on the stack */
double val[MAXVAL];	/* */
int buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

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

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	/* not a number */
	i = 0;
	if (isdigit(c))	/* accumulated floor */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')	/* accumulated ceiling */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	return NUMBER;
}


int getch(void)	/* input character (possibly returned to the stream) */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)	/* returning a character to the input stream */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
