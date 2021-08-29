/* K&R exercise 5.12 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000    /* maximum line length */
#define START   8
#define STEP    4

void entab(int *m, int *n);
int mygetline(char line[], int lim);
void detab(int *m, int *n);
void instab(int argc, int *m, int *n, char *argv[]);

int main(int argc, char *argv[])
{
    int m, n;

    instab(argc, &m, &n, argv);
    printf("-m = %d, +n = %d\n", m, n);
    //entab(&m, &n);
    detab(&m, &n);
    return 0;
}

void instab(int argc, int *m, int *n, char *argv[])
{
    if (argc == 3 &&
        *argv[1] == '-' && *argv[2] == '+') {    
        *m = atoi(&(*++argv)[1]);
        *n = atoi(&(*++argv)[1]);
    } else {
        *m = START;
        *n = STEP;  
    }
}

void detab(int *m, int *n)
{
    int c, i;
    int count = *m;
    
    while ((c = getchar()) != EOF) {
        if (c == '\t' && count == 0) {
            for (i = 0; i < *n; ++i)
                putchar(' ');
        }
        else {
            putchar(c);
        }
        if (count > 0)
            --count;
    }
}

void entab(int *m, int *n)
{
    int len;            /* line length */
    int count;          /* counter number of space */
    int i, j;
    char line[MAXLINE]; /* character string */
    
    count = 0;
    while ((len = mygetline(line, MAXLINE)) > 0)
        for(i = 0; i < len; ++i) {
            if (line[i] == ' ' && i >= *m) {
                ++count;
                if (count == *n) {
                    putchar('\t');
                    printf("%d", *n);
                    count = 0;
                }
            }
            else {
                if (count > 0 && count < *n)
                    for (j = 0; j < count; ++j)
                        putchar(' ');
                count = 0;
                putchar(line[i]);
            }
        }
}

int mygetline(char line[], int lim)
{
    int c, i;

    for (i = 0; i<lim-1 && ((c=getchar())!=EOF) && c!='\n'; ++i)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}
