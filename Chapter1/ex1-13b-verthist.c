/* Exercise 1-13 
 * 2nd version of K&R - program for displaying histogram
 * input stream word lengths version 2, with vertical columns 
 */
#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside word*/



int main()
{
    int c, word, state, linenumber;
    int lenword[10];

    word = linenumber = 0;
    state = OUT;
    for (int i = 0; i < 10; ++i)
        lenword[i] = 0;

    while ((c = getchar()) != EOF)
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            ++lenword[word];
            state = IN;
        }
        else
            if (state == IN) {
                if (linenumber < lenword[word])
                    linenumber = lenword[word];
                ++word;
                state = OUT;
            }
    for (int i = 0; i < word; ++i)
       printf("%d ", i + 1);
    printf("\n"); 
    for (int i = 0; i < linenumber; ++i) {
        for (int j = 0; j < word; ++j)
            if (lenword[j] > i)
                printf("# ");
               /* printf("%-*s", lenword[j] + 1, "#"); */
            else
                printf("  ");
                /* printf("%-*s", lenword[j] + 1, " "); */
        printf("\n");
    }

}
