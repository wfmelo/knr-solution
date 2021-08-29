/* Exercise 5-20.
 *
 * Expand dcl to handle declarations with function argument types, qualifiers
 * like const, and so on.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKEN 100
#define BUFSIZE  100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl(void);
void dirdcl(void);
int getch(void);
void ungetch(int c);
void dclspec(void);
//int typespec(void);
//int typequal(void);
//int compare(char **, char **);

int gettoken(void);
int tokentype;             /* last token type */
char token[MAXTOKEN];      /* last token entered */
char name[MAXTOKEN];       /* identifier name */
char datatype[MAXTOKEN];   /* data type = char, int, etc. */
char out[1000];            /* result string */
int prevtoken = NO;
char modificator[MAXTOKEN]; /* modifier name */

char buf[BUFSIZE];         /* buffer size for ungetch */
int bufp = 0;              /* next free position in buf */

int main()    /* converting ads into verbal form */    
{
    int mod = NO;
    
    while (gettoken() != EOF) {    /* 1st token in line */
        if (!(strcmp(token, "const")) || !(strcmp(token, "volatile"))) {
            strcpy(modificator, token); /* модификатор типа */
            mod = YES;
        } else
            strcpy(datatype, token);     /* type modifier */
        if (mod) {
            gettoken();
            strcpy(datatype, token);
        }
        out[0] = '\0'; 
        dcl();    /* parsing the rest of the string */
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s %s\n", name, out, mod ? modificator : "", datatype);
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
    void dclparam(void);

    if (tokentype == '(') {        /* ( ad ) */
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            prevtoken = YES;
        }
    } else if (tokentype == NAME)    /* variable name */
        if (name[0] == '\0')
            strcpy(name, token);
    else
        prevtoken = YES;
    while ((type=gettoken()) == PARENS || type == BRACKETS ||
           type == '(')
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(') {
            strcat(out, " func. taking");
            dclparam();
            strcat(out, " and return");
        }
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

void dclparam(void)
{
    do {
        dclspec();
    } while (tokentype == ',');
    if (tokentype != ')')
        printf("error: missed ) in declaration\n");
}

void dclspec(void)
{
    char temp[MAXTOKEN];
    int istypename(char []);
    int istypequal(char []);
     
    temp[0] = '\0';
    gettoken();
    //do {
        if (tokentype != NAME) {
            prevtoken = YES;
            dcl;
        } else if (istypename(token)) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else if (istypequal(token)) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else {
            printf("error: uknown type in list parametr\n");
            prevtoken = YES;
        }
        //} while (tokentype != ',' && tokentype != ')');
    strcat(out, temp);
    if (tokentype == ',')
        strcat(out, ", ");
}

 int istypename(char name[])
 {
     int i=0;
     char *types[] = {"char", "int", "float"};
     int ntypes = 3;

     while (ntypes--)
         if (strcmp(name, types[i++]) == 0)
             return 1;
     return 0;    
 }

 int istypequal(char qual[])
 {
     int i=0;
     char *quals[] = {"const", "volatile"};
     int nquals = 2;

     while (nquals--)
         if (strcmp(qual, quals[i++]) == 0)
             return 1;
     return 0;    
 }

/* typespec: returns YES if the given token  - */
/* type specifier */
/*int typespec(void)
{
    static char *types[] = {
        "char",
        "int",
        "void"
    };
    char *pt = token;

    if (bsearch(&pt, types, sizeof(types)/sizeof(char *),
       sizeof(char *), compare) == NULL)
            return NO;
        else
            return YES;
            }*/

/* typespec: вreturns YES if the given token is - */
/* type specifier */
 /*int typequal(void)
{
    static char *types[] = {
        "const",
        "volatile"
    };
    char *pt = token;

    if (bsearch(&pt, types, sizeof(types)/sizeof(char *),
       sizeof(char *), compare) == NULL)
            return NO;
        else
            return YES;
}

/* copare: compares two strings for a function bsearch */
/*int compare(char **s, char **t)
{
    return strcmp(*s, *t);
}*/
