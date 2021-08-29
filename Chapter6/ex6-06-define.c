/*
 * Exercise 6-6
 *
 * Implement a simple version of the #define processor (i.e., no arguments)
 * suitable for use with C programs, based on the routines of this section.  You
 * may also find getch and ungetch helpful.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHSIZE 101
#define BUFSIZE  100
#define MAXWORD  1000
#define CODE 0
#define PREPROC 1
#define COMMENT 2
#define SINGLE 3
#define DOUBLE 4

struct nlist *hashtab[HASHSIZE];    /* table of pointers */
int state = CODE;
int buf[BUFSIZE];
int bufp = 0;
char token[MAXWORD];
int stored = EOF;
char *ERROR = "ERROR";

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

struct nlist *install(char *name, char *defn);
struct nlist *nllookup(char *s);
char *lookup(char *s);
void undef(char *name);
unsigned hash(char *s);
char *strdup(const char *);
void ungetch(int c);
int getch(void);
char *gettoken(void);
int getch(void);
void ungetch(int c);
int parse(void);
char *preproc(char c);
char *code(char c);
char getpares(void);
char *checkdefines(char *name);
int asalnum(char c);
int asalpha(char c);

int main(void)
{
    char *t;
    
    while ((t = gettoken()) != NULL && t != ERROR)
        printf("%s", t);
    return 0;
}
char getparse(void)
{
    int c, temp;
    
    if (stored != EOF) {
        temp = stored;
        stored = EOF;
        return temp;
    } else {
        if ((c = parse()) == EOF)
            return EOF;
    }
    return c;
}
char *gettoken(void)
{
    int c;
    char *t = token;

    if ((c = getparse()) == EOF)
        return NULL;

    switch(state) {
    case CODE:
        t = code(c);
        break;
    case PREPROC:
        t = preproc(c);
        break;
    default:
        token[0] = c;
        token[1] = '\0';
        break;
    }
    return (t == NULL) ? gettoken() : t;
}

char *code(char c)
{
    char *t = token;

    *t++ = c;
    if (asalpha(c)) {
        while ((c = parse()) != EOF && state == CODE &&
               asalnum(c)) {
            *t++ = c;
        }
        stored = c;
    }
    *t = '\0';
    return checkdefines(token);
}

char *checkdefines(char *name)
{
	char *defn = lookup(name);
	return (defn == NULL) ? name : defn;
}


char *preproc(char c)
{
    char *name, *d, *t = token;

    if (c != '#') {
        printf("error: Expected '#' at start of preproc, got %d\n", c);
		return ERROR;
	}
	*(t++) = c;

    while ((c = parse()) != EOF && state == PREPROC) {
        *(t++) = c;
    }
    stored = c;
    *t = '\0';

    if (strncmp(token, "#define", 7) != 0 || !isspace(token[7]))
        return token;

    while (t > token && isspace(*(t - 1)))
        *--t = '\0';

    d = token + 7;
    while (isspace(*++d))
        ;

    name = d;
    if (!asalpha(*name)) {
        printf("error: Expected #define identifier (%s).\n", token);
        return ERROR;
    }
    while (asalnum(*++d))
        ;
    
    if (*d != '\0') {
        if (!isspace(*d)) {
            printf("error: Expected space after identifier: (%s)\n",
                   token);
            return ERROR;
        }
        *d = '\0';
        while (isspace(*++d))
            ;
    }
    install(name, d);
    return NULL;
}

int parse(void)
{
    int c;
    
    if ((c = getch()) == EOF)
        return EOF;
    switch(state) {
    case CODE:
        switch(c) {
        case '#':
            state = PREPROC;
            return c;
        case '/':
            if ((c = getch()) == EOF)
                return EOF;
            else if (c == '*') {
                state = COMMENT;
                stored = c;
            } else {
                ungetch(c);
            }
            return '/';
        case '"':
            state = DOUBLE;
            return c;
        case '\'':
            state = SINGLE;
            return c;
        default:
            return c;
        }
    case PREPROC:
        switch(c) {
        case '\n':
            state = CODE;
            return c;
        default:
            return c;
        }
    case COMMENT:
        switch(c) {
        case '*':
            if ((c = getch()) == EOF) {
                return c;
            } else if (c == '/') {
                state = CODE;
                stored = c;
                return '*';
            } else {
                ungetch(c);
                return '*';
            }
        default:
            return c;
        }
    case SINGLE:
        switch(c) {
        case '\'':
            state = CODE;
            return c;
        default:
            return c;
        }
    case DOUBLE:
        switch(c) {
        case '\\':
            if ((c = getch()) == EOF)
                return EOF;
            stored = c;
            return '\\';
        case '"':
            state = CODE;
            return c;
        default:
            return c;
        }
    default:
        printf("error: Unexpetced mode %d\n", state);
        return EOF;
    }
}

unsigned hash(char *s)
{
    unsigned hashval;
    
    for (hashval = 0; *s != '\0'; s++)
        hashval =  *s + 31 * hashval;
    return hashval % HASHSIZE;
}

char *lookup(char *s)
{
	struct nlist *nl = nllookup(s);
	return (nl == NULL) ? NULL : nl->defn;
}

struct nlist *nllookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    unsigned hashval;
    struct nlist *np;

    if ((np = nllookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(np));
        if (np == NULL || ((np->name = strdup(name)) == NULL))
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *) np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *name)
{
    if (name == NULL)
        return;
    else {
        unsigned hashval = hash(name);
        struct nlist *np = hashtab[hashval];
        struct nlist *prev = NULL;

        for ( ; np != NULL; prev = np, np = np->next)
            if (strcmp(name, np->name) == 0) {
                if (prev != NULL)
                    prev->next = np->next;
                else
                    hashtab[hashval] = np->next;
                free((void *) np->name);
                free((void *) np->defn);
                free((void *) np);
                return;
        }
    }
}

char *strdup(const char *s)
{
    char *p = (char *) malloc(strlen(s)+1);

    if (p != NULL)
        strcpy(p, s);
    return p;
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

int asalpha(char c)
{
	return isalpha(c) || (c == '_');
}


#define SORT_OF_LETTER asalpha(c)
#define NUMERAL isdigit(c)

int asalnum(char c)
{
	return SORT_OF_LETTER || NUMERAL;
}
