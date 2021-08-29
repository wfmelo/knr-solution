/*
 * Exercise 5-10.
 *
 * Write the program expr, which evaluates a reverse Polish expresion from
 * the command line, where each operator or operand is a separate argument.
 * For example,
 *
 * 	expr 2 3 4 + *
 *
 * evaluates 2 x (3+4).
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER '0'    /* number found */
#define MAXVAL 100
#define MAXOP  100   

void push(double);
double pop(void);
int getop(char *s);

int sp = 0;            /* next empty position in the stack */
double val[MAXVAL];    /* operand stack */

int main(int argc, char *argv[])
{
    double op2;
    char *s;
    
    while (--argc > 0) {
        switch (getop(s = *++argv)) {
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
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    printf("\t%.8g\n", pop());
    return 0;
}

int getop(char *s)
{
    int c;
    if (!isdigit(c = *s))
        return c;
    return NUMBER;
}

void push(double f)
{
    if (sp > MAXVAL)
        printf("error: stack is full can't push %g\n", f);
    else
        val[sp++] = f;
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
        printf("error: stack is empty\n");
    return 0.0;
}
