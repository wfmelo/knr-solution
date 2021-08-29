/* Exercise 5-18.
 *
 * Make dcl recover from input errors.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE  100
#define YES      1
#define NO       0

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int getch(void);
void ungetch(int c);

int gettoken(void);
int tokentype;             /* last token type */
char token[MAXTOKEN];      /* last token entered */
char name[MAXTOKEN];       /* identifier name */
char datatype[MAXTOKEN];   /* data type  = char, int etc. */
char out[1000];            /* result string */
int error = NO;

char buf[BUFSIZE];         /* buffer size for ungetch */
int bufp = 0;              /* next free position in buf  */

int main()    /* converting ads into verbal form */    
{
    while (gettoken() != EOF) {    /* 1-я token in string */
        strcpy(datatype, token);     /* data type */
        out[0] = '\0';
        dcl();    /* parsing the rest of the string */
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

int gettoken(void)    /* reads the next tokens */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (error == YES) {
        error = NO;
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
        for (*p++ = c; *p != ']'; ) {
            *p = getch();
            if (*p != ']') {
                if (*p == '\n' || *p == ')' || *p == '(') {
                    printf("error: mising ]\n");
                    ungetch(*p);
                    *p = ']';
                } else
                    *p++;
            }
        }
        *++p = '\0';
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

/* dcl: parsing a declaration */
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; )    /* counting characters */
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parsing direct declaration */
void dirdcl(void)
{
    int type;

    if (tokentype == '(') {        /* ( ad ) */
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            error = YES;
        }
    } else if (tokentype == NAME)    /* variable name */
        strcpy(name, token);
    else {
        printf("error: expected name or (dcl)\n");
        error = YES;
    }
    while ((type=gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
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
