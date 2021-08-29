/*
 * Exercise 6-2
 *
 * Write a program that reads a C program and prints in alphabetical order each
 * group of variable names that are identical in the first 6 characters, but
 * different somewhere thereafter.  Don't count words within strings and
 * comments.  Make 6 a parameter that can be set from the command line.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define DEFLEN  6
#define NKEYS     (sizeof reserved / sizeof (char *))

struct tnode {    /* tree node */
    char *word;            /* pointer to word text  */
    int count;
    struct tnode *left;    /* left child node */
    struct tnode *right;   /* right child node */
};

const char *reserved[] = { "auto", "break", "case", "char", "const",
                       "continue", "default", "do", "double",
                       "else", "enum", "extern", "float", "for",
                       "goto",  "if", "int", "long", "register",
                       "return", "short", "signed", "sizeof",
                       "static", "struct", "switch",  "typedef",
                       "union", "unsigned", "void", "volatile", "while" };

char group[MAXWORD];

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *, int len);
int getword(char *, int);
int isreserved(char *word, const char *key[], int n);

/* word frequency counting program */
int main(int argc, char **argv)
{
    struct tnode *root;
    char word[MAXWORD];
    int nsym;
    
    root = NULL;
    nsym = (argc == 2) ? atoi(argv[1]) : DEFLEN;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && !isreserved(word, reserved, NKEYS)
            && strlen(word) >= nsym)
            root = addtree(root, word);

    treeprint(root, nsym);
    return 0;
}

/* isresereved: return 1 if word in key else return 0 */
int isreserved(char *word, const char *reserved[], int n)
{
    int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, reserved[mid])) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return 1;
	}
	return 0;
}

struct tnode *talloc(void);
char *strdupp(char *);

/* addtree: adding a node with the word w to node p or below */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {    /* new words arrived */
        p = talloc();   /* a new node is created */
        p->word = strdupp(w);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)     /* the smaller one goes to the left subtree */
        p->left = addtree(p->left, w);
    else if (cond > 0)                   /* the bigger one goes to the right subtree */
        p->right = addtree(p->right, w);
    return p;
}

/* treeprint: output tree p in alphabetical order */
void treeprint(struct tnode *p, int n)
{
    static struct tnode *previous;
    static int flag = 0;
    
    if (p != NULL) {
        treeprint(p->left, n);
        if (n == 0)
            printf("%4d %s\n", p->count, p->word);
        else {
            if (previous == NULL || strncmp(p->word, group, n) != 0) {
                strncpy(group, p->word, n);
                printf("%s:\n", group);
            }
            printf("\t%s\n", p->word);
            previous = p;
        }
        treeprint(p->right, n);
    }
}

/* talloc: creating a tree node of type tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdupp(char *s)    /* duplicate string s */
{
    char *p;

    p = (char *) malloc(strlen(s)+1);    /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int bufp = 0;
char buf[100];

/* getword: reads the next word or character from the input stream */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c == '"')
        while ((c = getch()) != '"') {
            if (c == '\\')
                getch();
            else
                continue;
        }
    if (c == '/') {
        if ((c = getch()) == '*') {
            while ((c = getch()) != EOF)
                if (c == '*')
                    if ((c = getch()) == '/')
                        break;
        }
        else if (c == '/')
            while ((c = getch()) != '\n')
                continue;
        else
            ungetch(c);
    }
    if (c == '#')
        while ((c = getch()) != EOF && c != '\n')
            continue;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '_' && c != '#') {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp < 100)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}
