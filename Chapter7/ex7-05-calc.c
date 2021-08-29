/*
 * Exercise 7-5.
 *
 * Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do
 * the input and number cnversion.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP    100
#define NUMBER   '0'

int getop(double *);
void push(double);
double pop(void);

int main(void)
{
    int type;
    double op2;
    double val;

    while ((type = getop(&val)) != EOF) {
        switch (type) {
        case NUMBER:
            push(val);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '*':
            push(pop() * pop());
            break;
        case '/':
            op2  = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '=':
			printf("\t%.8g\n", pop());
			break;
        default:
            printf("error: unknown command %c\n", type);
            break;
        }
    }
    return 0;
}

#define MAXVAL   100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(double *val)
{
    int c;
    char s[MAXOP];
    
    if (scanf("%s", s) != 1)
        return EOF;
    if (sscanf(s, "%lf", val) == 1)
        return NUMBER;
    if (s[1] != '\0') {
		printf("error: don't know how to parse: %s\n", s);
		return EOF;
    }
    return s[0];
}
