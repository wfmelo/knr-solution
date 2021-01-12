/* Exercise 4-3
 *
 * Given the basic framework, it's straightforward to extend the calulator.
 * Add the modulus (%) operator and provisions for negative numbers
 *
 */
#include <stdio.h>
#include <stdlib.h>	/* for declarate atof() */
#include <ctype.h>

#define MAXOP	100	/* maximum size operand or sign */
#define NUMBER	'0'	/* the signal that number found */
#define MAXVAL 100	/* maximum stack depth */
#define BUFSIZE 100
#define UNARY	'#'	/* unary minus for working with negative numbers */

int getop(char s[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0;			/* next free position on the stack */
double val[MAXVAL];	/* operand stack */
char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

/* reverse polish calculator */
int main()
{
	int type;
	double op1, op2, mod;
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
		case UNARY:
			push(0 - pop());
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0) {
				if ((op1 = pop()) < 0)
					mod = -op1;
				else
					mod = op1;
				if (op2 < 0)
					op2 = -op2;
				while (mod >= op2)
					mod = mod - op2;
				if (op1 < 0)
					mod = -mod;
				printf("%g %g\n", op1, op2);
				push(mod);
			}
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
	if (!isdigit(c) && c != '.' && c != '-')
		return c;	/* not a number */
	i = 0;
	if (c == '-') {
		s[i] = c;
		if (!isdigit(c = getch()))
			return '-';
		s[++i] = c;
	}
	if (isdigit(c))	/* accumulated floor */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')	/* accumulated ceiling */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}


int getch(void)	/* character input (possibly returned to the stream) */
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
