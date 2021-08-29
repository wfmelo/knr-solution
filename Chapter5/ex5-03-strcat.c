/*
 * Exercise 5-3
 *
 * Write a pointer version of the function strcat that we showed in Chapter
 * 2: strcat(s, t) copies the string t to the end of s.
 */
#include <stdio.h>

void strcatp(char *s, const char *t);
void strcata(char s[], const char t[]);

int main()
{
    char s[14] = "Hello, ";
    char t[] = "World!";

    strcata(s, t);
    printf("%s\n", s);
    return 0;
}

void strcatp(char *s, const char *t)
{   
    while (*s)
        ++s;
    while (*s++ = *t++)
        ;
}

void strcata(char s[], const char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')
        i++;
    while ((s[i++] = t[j++]) != '\0')
        ;
}
