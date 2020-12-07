/* Exercise 1-15.
Rewrite the temperature conversion program of Section 1.2 to use a function
for conversion.
*/
#include <stdio.h>

#define LOWER   0       /* lower limit of temperature */       
#define UPPER   300     /* upper limit */
#define STEP    20      /* step size */

float cels(int temp);

int main()
{
    int fahr;

    fahr = LOWER;
    while (fahr <= UPPER) {
        printf("%3d %6.1f\n", fahr, cels(fahr));
        fahr = fahr + STEP;
    }
    return 0;
}

float cels(int temp)
{
    return (5.0/9.0) * (temp - 32);
}
