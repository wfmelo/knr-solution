/*
 * Exercise 5-3
 *
 * Write the function strend(s,t) , which returns 1 if the string t occurs
 * at the end of the string s, and zero otherwise.
 */
#include <stdio.h>

int strend(char *s, char *t);

int main()
{
    char s[] = "Hello, World!";
    char t[] = "World!";
    char f[] = "world!";
    
    printf("%s\n", s);
    printf("%d\n", strend(s, t));
    return 0;
}

int strend(char *s, char *t)
{
    char *ps = s;
    char *pt = t;
    
    while (*s)
        ++s;
    while (*t)
        ++t;
    for ( ; *s == *t; s--, t--)
        if (s == ps || t == pt)
            break;
    if (*s == *t && t == pt && *s != '\0')
        return 1;
    return 0;
}
