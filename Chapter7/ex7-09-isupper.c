/*
 * Exercise 7-9
 * 
 * Functions like isupper can be implemented to save space or to save time.  
 * Explore both possibilities.
 */
#include <stdio.h>
#include <string.h>

/* optimized for space */
static int sisupper(int c);

/* optimized for time */
static int tisupper(int c);

int main(void)
{
    printf("%d\n%d\n", sisupper('A'), tisupper('A'));
    printf("%d\n%d\n", sisupper('b'), tisupper('b'));
    return 0;
}

int sisupper(int c)
{
    return 'A' <= c && c <= 'Z';
}
int tisupper(int c)
{
	return (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL); 
}
