/* Exercise 4-6
 *
 * Add commands for handling variables.  (It's easy to provide twenty-six 
 * variables with single-letter names.)  Add a variable for the most 
 * recently printed value.
 */
#include <stdio.h>
#include <stdlib.h>	/* для объявления atof() */
#include <ctype.h>
#include <math.h>

#define MAXOP	100	/* maximum size operand or sign */
#define NUMBER	'0'	/* the signal that number found */
#define MAXVAL 100	/* maximum stack depth */
#define BUFSIZE 100
#define UNARY	'#'	/* unary minus for working with negative numbers */
#define SUB		'$'	/* subtraction */
#define DUP		'~'	/* create a duplicate of the top item on the stack */
#define PRINT	'='	/* print stack */
#define CLEAR	'_'	/* clear stack */
#define LAST 	'!'	/* pop the top element of the stack without removing */
#define SWAP	'@'	/* swap top elements */
#define SIN		'1' /* sin */
#define VAR		'2'

int getop(char s[]);
void push(double);
double pop(void);
double peek(void);
void swap(void);
void print_stack(void);
void clear_stack(void);
int getch(void);
void ungetch(int);
void math_oper(char s[]);

int sp = 0;			/* next free position on the stack */
double val[MAXVAL];	/* operand stack */
char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */
double variable[26] = {0};
double V;
int var = 0;

/* reverse polish calculator */
int main()
{
	int type;
	double op1, op2, mod, last, res;
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
		case MATH:
			math_oper(s);
			break;
		case VAR:
			if (var >= 97 && var <= 122)
				push(variable[var-97]);
			else
				printf("ERROR: variable is not valid");
			break;
		case '=':
			pop();
			if (var >= 97 && var <= 122)
				variable[var - 97] = pop();
			else
				printf("ERROR");
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
			V = peek();
			print_stack();
			break;
		default:
		 	if (type == 'V')
				printf("V: %.8g\n", V);
			else
				printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

/* push: pushes the number f onto the operand stack*/
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pops and returns the top number from the stack  */
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

/* swap: swap top elements */
void swap(void)
{
	double a = pop();
	double b = pop();

	push(a);
	push(b);
}

void math_oper(char s[])
{
	int c;
	
	if (s[0] == 's' && s[1] == 'i' && s[2] == 'n')
		push(sin(pop()));
	else if (s[0] == 'c' && s[1] == 'o' && s[2] == 's')
		push(cos(pop()));
	else if (s[0] == 'e' && s[1] == 'x' && s[2] == 'p')
		push(exp(pop()));
	else
		printf("Error: operation does not exist\n");
}


/* getop: retrieves the next operand or token of an operation */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	i = 0;
	while (c >= 97 && c <= 122)
		if (i < 2) {
			s[i++] = c;
			c = getch();
		}
		else
			break;
	if (i == 2) {
		s[i++] = c;
		s[i] = '\0';
		return MATH;
	}
	else if (i == 1) {
		var = s[0];
		return VAR;
	}
	if (!isdigit(c) && c != '.' && c!='-' && c!='!' && c!='^' && c!='~')
		return c;	/* not a number */
	if (c == '^' || c == '!' || c == '~') {
		s[i] = c;
		while((c = getch()) != '\n')
			;
		if (s[i] == '^')
			return PRINT;
		else if (s[i] == '!')
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

/*
a = 2 1 + sin
	var['a'] = sin(3);
stack:
2 1
3 sin
sin(3)*/
