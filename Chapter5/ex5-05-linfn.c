/*
 * Exercise 5-5.
 * 
 * Write versions of the library functions strncpy, strncat, and strncmp, 
 * which operate on at most the first n characters of their argument 
 * strings.  For example, strncpy(s, t, n) copies at most n characters of t
 * to s.  Full descriptions are in Appendix B.
 */
#include <stdio.h>
#include <string.h>

char *mystrncpy(char *s, char *t, int n);
char *mystrncat(char *s, char *ct, int n);
int mystrncmp(char *cs, char *ct, int n);

int main()
{
    char t[] = "Hello, world!";
    char ct[] = "This is The end!";
    char cs[] = "This is the end!";
    char *ptr, s[32];
    int i;

    ptr = mystrncpy(s, t, 13);
    printf("%s\n", s);
    printf("%p\n", &s);
    printf("%p\n", ptr);

    ptr = (mystrncat(s, ct, 7));
    printf("%s\n", s);

    i = mystrncmp(cs, ct, 10);
    printf("i = %d\n", i);
    
    return 0;
}

/* strncpy: copy no more n symbols in string t to s: return s. */
char *mystrncpy(char *s, char *t, int n)
{
    char *ptrs = s;
    
    while (n--) {
        if (*t == '\0')
            break;
        *s++ = *t++;
    }
    *s = '\0';
    return ptrs;
}

/* strncpy: concat no more n symobls in strings ct to s: return s. */
char *mystrncat(char *s, char *ct, int n)
{
    char *ptrs = s;
    
    while (*s)
        s++;
cd    while (n--) {
        if (*ct == '\0')
            break;
        *s++ = *ct++;
    }
    *s = '\0';
    return ptrs;
}

/* strncpy: compares no more n symbols in strings cs and ct;
 * return <0 if cs<ct; 0, if cs==ct; and >0, if cs>ct */
int mystrncmp(char *cs, char *ct, int n)
{
    for ( ; *cs == *ct && n; cs++, ct++, n--)
        if (*cs == '\0')
            return 0;
    return *cs - *ct;
}
