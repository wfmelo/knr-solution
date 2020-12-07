/* Exercise 1-14.
Write a program to print a histogram of the frequencies of different
characters in its output.
*/
#include <stdio.h>

int main()
{
    int c;
    int numbchar[127];

    for (int i = 0; i < 127; ++i)
        numbchar[i] = 0;
    while ((c = getchar()) != EOF)
        ++numbchar[c];

    for (int i = 0; i < 127; ++i)
        if (numbchar[i] != 0) {
            if (i >= 32 && i <= 126)
                printf("'%c' ", i);
            else if (i == 9)
                printf("%s  ", "\\t");
            else if (i == 10)
                printf("%s  ", "\\n");
            for (int j = 0; j < numbchar[i]; ++j)
                printf("#");
            printf("\n");
        }
}
