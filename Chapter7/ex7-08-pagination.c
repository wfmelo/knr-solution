/*
 * Exercice 7-8.
 *
 * Write a program to print a set of files, starting each new one one new page,
 * with a title and a running page count for each file.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

static void printfile(char *file);

static int page = 1;
static long lineno = 1;

int main(int argc, char *argv[])
{
    int i;
    
    if (argc <= 1) {
        fprintf(stderr, "Usage: %s file1 file2 ... fileN\n", argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++)
        printfile(argv[i]);
    return 0;
}

void printfile(char *file)
{
    FILE *fp;
    static char line[MAXLINE];

    if ((fp = fopen(file, "r")) == NULL) {
        fprintf(stderr, "Error: open file %s\n", file);
        exit(1);
    }    
    fprintf(stdout, "#FILE: %-55.60s\tPage %d\n", file, page++);
    while (fgets(line, MAXLINE, fp) != NULL) {
        fprintf(stdout, "%ld ", lineno++);
        fputs(line, stdout);
    }
}
