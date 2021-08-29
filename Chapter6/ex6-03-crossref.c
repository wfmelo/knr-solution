/*
 * Exercise 6-3.
 *
 * Write a cross-referencer that prints a list of all words in a document, and,
 * for each word, a list of the line numbers on which it occurs.  Remove noise
 * words like "the," "and," and so on.
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

struct list {
    int nline;
    struct list *next;
};

struct tnode {
    char *word;
    struct list *lines;
    struct tnode *left;
    struct tnode *right;
};

char buf[BUFSIZE];
int bufp = 0;

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

int getword(char *word, int lim, long *nline)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        if (c == '\n')
            (*nline)++;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
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

int isnoise(char *word)
{
    const char *nw[] = {
        "a", "an", "and", "are", "for",
		"from", "in", "is", "it", "not",
        "of", "on", "or", "that","the",
        "this", "to", "was", "with"
    };
    int low = 0;
    int high = sizeof(nw) / sizeof(nw[0]) - 1;
    int cond, mid;

    if (word[1] == '\0')
        return 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, nw[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else 
            return 1;
    }
    return 0;
}

void freelist(struct list *lnode)
{
    if (lnode == NULL)
        return;
    freelist(lnode->next);
    free(lnode);
}

void freetree(struct tnode *tnode)
{
    if (tnode == NULL)
        return;
    freetree(tnode->left);
    freetree(tnode->right);
    free(tnode->word);
    freelist(tnode->lines);
    free(tnode);
}
    

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

struct list *lalloc(void)
{
    return (struct list *) malloc(sizeof(struct list));
}

char *strdupp(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s)+1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

struct list *addline(struct list *p, long nline)
{
    if (p == NULL) {
        if ((p = lalloc()) == NULL)
            return NULL;
        p->nline = nline;
        p->next = NULL;
    } else if (p->nline == nline)
        return p;
    else {
        if ((p->next = addline(p->next, nline)) == NULL)
            return NULL;
    }
    return p;
}

struct tnode *addtree(struct tnode *p, char *w, long nline)
{
   int cond;
   struct list *n;

   if (p == NULL) {
       p = talloc();
       p->word = strdupp(w);
       p->left = p->right = NULL;
       if ((p->lines = addline(NULL, nline)) == NULL)
           return NULL;
   } else if ((cond = strcmp(w, p->word)) == 0) {
       if ((p->lines = addline(p->lines, nline)) == NULL)
           return NULL;
    }
    else if (cond < 0)
        p->left = addtree(p->left, w, nline);
    else if (cond > 0)
        p->right = addtree(p->right, w, nline);
    return p;
}

void listprint(struct list *p)
{
    if (p != NULL) {
        printf("%d ", p->nline);
        listprint(p->next);
    }
}

void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%s: ", p->word);
        listprint(p->lines);
        printf("\n");
        treeprint(p->right);
    }
}

int main(int argc, char **argv)
{
    struct tnode *root;
    long nline = 1;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD, &nline) != EOF)
        if (isalpha(word[0]) && !isnoise(word))
            root = addtree(root, word, nline);
    treeprint(root);
    freetree(root);
    return 0;
}
/*Write a cross-referencer that prints a list of all words in a document, and,
for each word, a list of the line numbers on which it occurs.  Remove noise
words like "the," "and," and so on.*/
