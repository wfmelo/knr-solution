/*
 * Exercise 7-7.
 *
 * Modify the pattern finding program of Chapter 5 to take its input from a set
 * of named files or, if no files are named as arguments, from the standard
 * input.  Should the file name be printed when a matching line is found?
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000

struct options {
    int except;
    int number;
    int filename;
    char *pattern;
    int pathargs;
};

static int findpattern(FILE *file, char *path, struct options *);
static void parseargs(int argc, char **argv, struct options *);
static FILE *chkfopen(char *path, char *modes);
static char *chkfgets(char *s, int n, FILE *iop, char *path);

static char errormsg[MAXLINE];

int main(int argc, char *argv[])
{
    struct options options;
    int i, found = 0;
    FILE *file;
    char *path;
    
    parseargs(argc, argv, &options);
    if (options.pathargs < argc)
        for (i = options.pathargs; i < argc; i++) {
            path = argv[i];
            file = chkfopen(path, "r");
            found += findpattern(file, path, &options);
            fclose(file);
        }
    else
        found = findpattern(stdin, "<stdin>", &options);

    return 0;
}

void parseargs(int argc, char **argv, struct options *options)
{
    int c, i;
    char *arg;

    options->except = options->number = options->filename = 0;
    for (i = 1; i < argc && (arg = argv[i])[0] == '-'; i++)
        while (c = *++arg)
            switch(c) {
            case 'x':
                options->except = 1;
                break;
            case 'n':
                options->number = 1;
                break;
            case 'f':
                options->filename = 1;
                break;
            default:
                fprintf(stderr, "find: illegal option %c\n", c);
                exit(1);
            }
    if (i == argc) {
        fprintf(stderr, "Usage: find -x -n -f pattern\n");
        exit(1);
    } else {
       options->pattern = argv[i++];
       options->pathargs = i;
    }
}

int findpattern(FILE *file, char *path, struct options *options)
{
    char line[MAXLINE];
    long lineno = 0, found = 0;

    while (chkfgets(line, MAXLINE, file, path) != NULL) {
        lineno++;
        if ((strstr(line, options->pattern) != NULL) != options->except) {
            if (options->filename)
                printf("%s:", path);
            if (options->number)
                printf("%ld:", lineno);
            printf("%s", line);
            found++;
        }
    }
    return found;
}

FILE *chkfopen(char *path, char *modes)
{
	FILE *fp = fopen(path, modes);
	if (fp != NULL)
		return fp;
	sprintf(errormsg, "error: Failed to open file: '%s'", path);
	perror(errormsg);
	exit(1);
}

char *chkfgets(char *s, int n, FILE *iop, char *path)
{
	char *r = fgets(s, n, iop);
	if (!ferror(iop))
		return r;
	sprintf(errormsg, "error: Failed to read file: '%s'", path);
	perror(errormsg);
	fclose(iop);
	exit(1);
}
