/*
 * Exercise 7-6.
 *
 * Write a program to compare two files, printing the first line where they
 * differ.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1 << 10

int main(int argc, char **argv)
{
    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE];
    char *prog = argv[0];
    char *res1, *res2;
    int lnnum = 0;

    if (argc == 3) {
        if ((fp1 = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", argv[1], prog);
            exit(1);
        }
        if ((fp2 = fopen(argv[2], "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", argv[2], prog);
            exit(1);
        }
    } else {
        fprintf(stderr, "Usage: %s file1 file2\n", prog);
        exit(1);
    }
    do {
        lnnum++;
        if ((res1 = fgets(line1, MAXLINE, fp1)) == NULL)
            fprintf(stderr, "error reading file %s\n", argv[1]);
        if ((res2 = fgets(line2, MAXLINE, fp2)) == NULL)
            fprintf(stderr, "error reading file %s\n", argv[2]);
    } while (res1 && res2 && !strcmp(res1, res2));
    if (res1 != res2)
        printf("line: %d\n< %s---\n> %s", lnnum,
		       res1 ? res1 : "<EOF>\n", res2 ? res2 : "<EOF>\n");
    if (fp1 != NULL)
        fclose(fp1);
    if (fp2 != NULL)
        fclose(fp2);
    return 0;
}
