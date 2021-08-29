/*
 * Exercise 5-19.
 *
 * Modify undcl so that it does not add redundant parentheses to declarations.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE  100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

int getch(void);
void ungetch(int c);

int gettoken(void);
int nexttoken(void);
int tokentype;             /* last token type */
char token[MAXTOKEN];      /* last token entered */
char name[MAXTOKEN];       /* identifier name */
char datatype[MAXTOKEN];   /* data type = char, int, etc.  */
char out[1000];            /* result string */
int prevtoken;

char buf[BUFSIZE];         /* buffer size for ungetch */
int bufp = 0;              /* next free position in buf */

/* undcl: translation of verbal descriptions into ads */
int main()    /* converting ads into verbal form */    
{
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                if ((type = nexttoken()) == PARENS || type == BRACKETS)
                    sprintf(temp, "(*%s)", out);
                else
                    sprintf(temp, "*%s", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
        }
        printf("%s \n", out);
    }
    return 0;
}

int gettoken(void)    /* reads the next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (prevtoken == YES) {
        prevtoken = NO;
        return tokentype;
    }
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

int nexttoken(void)
{
    int type;

    type = gettoken();
    prevtoken = YES;
    return type;
}
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar(); 
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
