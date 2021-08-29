/*
 * Exercise 6-4.
 *
 * Write a program that prints the distinct words in its input sorted into
 * decreasing order of frequency of occurrence.  Precede each word by its count.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

#define SPEED "speed"
#define COLOUR "color"
#define ANIMAL "animal"

struct nlist { /* table entry */
    struct nlist *next;    /* next entry in the chain */
    char *name;            /* name after #define */
    char *defn;            /* inline text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
int arr[10];

struct nlist *lookup(char *);
char *strdup(const char *);

/* hash: generating a hash code for a string s */
unsigned hash(char *s)
{
    return 0;
    /*unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
        return hashval % HASHSIZE;*/
}

/* lookup: search for element s in a table hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;    /* item found */
    return NULL;          /* item not found */
}

/* install: puts an entry "name + definition"
 *     (name, defn) in table hashtab
*/
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {    /* name not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else    /* already in the table */
        free((void *) np->defn);    /* removing the old definition */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

char *defn(struct nlist *np)
{
	return np ? np->defn : "????";
}

void settab(void)
{
	int i;
	for (i = 0; i < HASHSIZE; i++)
		hashtab[i] = NULL;
	install(SPEED, "quick");
	install(COLOUR, "brown");
	install(ANIMAL, "fox");
}

void display(void)
{
	printf("The %s, %s %s jumped over the lazy dog.\n", defn(lookup(SPEED)),
	       defn(lookup(COLOUR)), defn(lookup(ANIMAL)));
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

int main(void)
{
    struct nlist *p;
    int i;
    clock_t t;

    settab();
	display();

	settab();
	undef(SPEED);
	display();

	settab();
	undef(COLOUR);
	display();

	settab();
	undef(ANIMAL);
	display();

    return 0;
}
