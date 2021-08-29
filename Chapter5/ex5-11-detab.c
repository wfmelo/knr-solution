/* Exercise 5-11
 *
 * Modify the programs entab and detab (written as exercises in Chapter 1)
 * to accept a list of tab stops as arguments.  Use the default tab settings
 * if there are no arguments.
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define YES 1        /* Setpoint available */
#define NO  0        /* Setpoint unavailable */
#define SIZE 4        /* Size of the original argument list */
#define MAXLINE 1000

void detab(char *list[], char *argv[], int argc);
int select_list(int argc, int *setting);
char **start_of_list(char *list[], char *argv[], int setting);
int tab_len(char **p, int n);
void entab(char *list[], char *argv[], int argc);
int mygetline(char line[], int lim);

int main(int argc, char *argv[])
{
	char *list[SIZE] = {"8", "4", "2", "1"};
    
    detab(list, argv, argc);
    entab(list, argv, argc);
    return 0;
}

/* select_list: selects a list of arguments and returns the size of the list */
int select_list(int argc, int *setting)
{
    if (argc > 1) {
        *setting = NO;
        return argc - 1;
    }
    *setting = YES;
    return SIZE;
}
/* start_of_list: returns the beginning of the list */
char **start_of_list(char *list[], char *argv[], int setting)
{
    if (setting == YES)
        return list;
    return argv + 1;
}

void detab(char *list[], char *argv[], int argc)
{
    int c, n, i, count, len, setting;
    char **p = list;

    len = select_list(argc, &setting);
    count = len;
    while ((c = getchar()) != EOF) {
        if (c == '\n' || count == len) {
            p = start_of_list(list, argv, setting);
            count = 0;
        }
        n = tab_len(p, n);
        //printf("%d", n);
        if (c == '\t') {
            for (i = 0; i < n; ++i)
                putchar(' ');
            *++p;
            count++;
        }
        else
            putchar(c);
    }
}

int tab_len(char **p, int n)
{
    if (atoi(*p))
        return atoi(*p);
    return n;
}
/* mygetline: function read input sting and return length. */
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

void entab(char *list[], char *argv[], int argc)
{
    int len;             /* length string */
    int count1 = 0;          /* counter of space */
    int count2 = 0;          /* counter of tab */
    int lenlst;          /* length of the argument list */
    int setting, n = 0, i, j;
    char line[MAXLINE];  /* character string */
    char **p = list;

    lenlst = select_list(argc, &setting);
    p = start_of_list(list, argv, setting);
    n = tab_len(p, n);
    while ((len = mygetline(line, MAXLINE)) > 0)
        for(i = 0; i < len; ++i) {            
            if (line[i] == ' ') {
                ++count1;
                if (count1 == n) {
                    putchar('\t');
                    count1 = 0;
                    //printf("%d", n);
                    n = tab_len(++p, n);
                    count2++;
                    if (count2 == lenlst) {
                        p = start_of_list(list, argv, setting);
                        n = tab_len(p, n);
                        count2 = 0;
                    }
                }
            }
            else {
                if (count1 > 0 && count1 < n)
                    for (j = 0; j < count1; ++j)
                        putchar(' ');
                count1 = 0;
                if (line[i] == '\n') {
                    p = start_of_list(list, argv, setting);
                    n = tab_len(    p, n);
                    count2 = 0;
                }
                putchar(line[i]);
            }
        }
}
