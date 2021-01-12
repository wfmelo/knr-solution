/* Exercise 4-4
 *
 * Add commands to print the top element of the stack without poping, to
 * duplicate it, and to swap the top two elements.  Add a command to clear
 * the stack.
 */
#include <stdio.h>
#include <stdlib.h>	/* for declarate atof() */
#include <ctype.h>

#define MAXOP	100	/* maximum size operand or sign */
#define NUMBER	'0'	/* the signal that number found */
#define MAXVAL 100	/* maximum stack depth */
#define BUFSIZE 100
#define UNARY	'#'	/* unary minus for working with negative numbers */
#define SUB		'$'	/* subtraction */
#define DUP		'~'	/* create a duplicate of the top item on the stack */
#define PRINT	'='	/* print stack */
#define CLEAR	'_'	/* clear stack */
#define LAST 	'p'	/* pop the top element of the stack without removing */
#define SWAP	'@'	/* swap top elements */

int getop(char s[]);
void push(double);
double pop(void);
double peek(void);
void swap(void);
void print_stack(void);
void clear_stack(void);
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
	double op1, op2, mod, last;
	char s[MAXOP];

	last = 0;
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case LAST:
			printf("Last element: %.8g\n", peek());
			break;
		case DUP:
			last = pop();
			push(last);
			push(last);
			break;
		case PRINT:
			print_stack();
			break;
		case CLEAR:
			clear_stack();
			break;
		case SWAP:
			swap();
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
		case SUB:
			op2 = pop();
			push(pop() - op2);
			print_stack();
			break;
		case '\n':
			print_stack();
			//printf("\t%.8g\n", pop());
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
		printf("error: stack full, can't push %g\n", f);
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

/* peek: returns the top number from the stack */
double peek(void)
{
	if (sp != 0)
		return val[sp-1];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* print_stack: print stack */
void print_stack(void)
{
	int i;

	if (sp > 0) {
		printf("Stack: ");
		for (i = 0; i < sp; i++)
			printf("%g ", val[i]);
		printf("\n");
	}
	else
		printf("Stack is empty\n");
}

/* clear_stack: clear stack */
void clear_stack(void)
{
	sp = 0;
	printf("Stack cleared\n");
}

void swap(void)
{
	double a = pop();
	double b = pop();

	push(a);
	push(b);
}

/* getop: retrieves the next operand or token of an operation */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c!='-' && c!='p' && c!='=' && c!='~')
		return c;	/* not a number */
	i = 0;
	if (c == '=' || c == 'p' || c == '~') {
		s[i] = c;
		while((c = getch()) != '\n')
			;
		if (s[i] == '=')
			return PRINT;
		else if (s[i] == 'p')
			return LAST;
		else if (s[i] == '~')
			return DUP;
	}
	if (c == '-') {
		s[i] = c;
		if (!isdigit(c = getch()))
			return SUB;
		else
			ungetch(c);
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
