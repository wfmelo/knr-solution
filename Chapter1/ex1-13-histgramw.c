/* Exercise 1-13. 
Write a program to print a histogram of the lengths of words in its input. 
It is easy to draw the histogram with the bars horizontal; a vertical 
orientation is more challenging.
*/
#include <stdio.h>
#define IN  1   /* inside a word */
#define OUT 0   /* outside the word*/

int main()
{
    int c, i, j, word, state;
    int lenwords[10];

    state = OUT;
    word = 0;
    for (i = 0; i < 10; ++i)
        lenwords[i] = 0;

    while ((c = getchar()) != EOF) {
        if ((c >= 'a' && c  <= 'z') || (c >= 'A' && c <= 'Z')) {
            state = IN;
            ++lenwords[word];
        }
        else
            if (state == IN) {
                ++word;
                state = OUT;
            }
    }
    for (i = 0; i < word; ++i) {
        printf("%d   ", i + 1);
        for (j = 0; j <= lenwords[i] - 1; ++j)
            printf("#");
        printf("\n");
    }
}
