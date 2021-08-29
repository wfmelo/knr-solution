/*
 * Exercise 6-4.
 *
 * Write a program that prints the distinct words in its input sorted into
 * decreasing order of frequency of occurrence.  Precede each word by its coliunt.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFFSIZE 100

static char buf[BUFFSIZE];
static int bufp = 0;

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(const char *s)
{
    char *p = (char *) malloc(strlen(s)+1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

struct tnode *addword(struct tnode *p, char *word)
{
    int cond;
    
    if (p == NULL) {
        if ((p = talloc()) == NULL)
            return NULL;
        p->word = strdup(word);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(word, p->word)) == 0)
        p->count++;
    else if (cond < 0) {
        if ((p->left = addword(p->left, word)) == NULL)
            return NULL;
    } else {
        if ((p->right = addword(p->right, word)) == NULL)
            return NULL;
    }
    return p;
}

int treetoarray(struct tnode *p, struct tnode **warray, int i)
{
    if (p == NULL)
        return i;

    warray[i++] = p;
    if (p->left != NULL)
        i = treetoarray(p->left, warray, i);
    if (p->right != NULL)
        i = treetoarray(p->right, warray, i);
    return i;
}

int treesize(struct tnode *node)
{
    int ct = 1;
    
    if (node == NULL)
        return 0;
    else {
        ct += treesize(node->left);
        ct += treesize(node->right);
        return ct;
    }
}

int compare(struct tnode *a, struct tnode *b)
{
    return b->count - a->count;
}

void quicksort(void **v, int left, int right,
               int (*comp)(void *, void *))
{
    int i, last;
    void swap(void **v, int i, int j);
    
    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last  = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last-1, comp);
    quicksort(v, last+1, right, comp);
}

void swap(void **v, int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void freetree(struct tnode *p)
{
    if (p == NULL)
        return;
    freetree(p->left);
    freetree(p->right);
    free(p->word);
    free(p);
}   

int main(void)
{
    char word[MAXWORD];
    struct tnode *root = NULL;
    struct tnode **warray = NULL;
    int wsize, i;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((root = addword(root, word)) == NULL)
                return 1;
    
    wsize = treesize(root);
    warray = (struct tnode **) malloc(wsize * sizeof(struct tnode *));
    if (warray == NULL)
        return 1;
    treetoarray(root, warray, 0);
    quicksort((void **)warray, 0, wsize-1, (int (*)(void *, void*))compare);
    for (i = 0; i < wsize; i++)
        printf("%4d %s\n", warray[i]->count, warray[i]->word);

    freetree(root);
    free(warray);
    return 0;
}

/*
struct list {
    char *word;
    long count;
    struct list *next;
};
*/

/*
struct list *lalloc(void)
{
    return (struct list *) malloc(sizeof(struct list));
}
*/

/*
struct list *addtolist(struct list *p, char *word)
{
    if (p == NULL) {
        if ((p = lalloc()) == NULL)
            return NULL;
        p->word = strdupp(word);
        p->count = 1;
        p->next = NULL;
    } else if (strcmp(p->word, word) == 0)
        p->count++;
    else
        if ((p->next = addtolist(p->next, word)) == NULL)
            return NULL;
    return p;
}
*/
/*
void printlist(struct list *p)
{
    printf("%s: %ld\n", p->word, p->count);
    if (p->next != NULL)
        printlist(p->next);
}
*/
