/* print Celsius-Fahrenhiet table
    for celsius - -20, -10, ..., 150 */
#include <stdio.h>

int main()
{
	float fahr, celsius;
	float lower, upper, step;

	lower = -17.8;	/* lower limit of temperature */
	upper = 148.9;	/* upper limit */
	step = 11.1;	/* step size */

	printf("%7s %7s\n", "°C", "°F");
	celsius = lower;
	while (celsius <= upper) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%6.1f %6.2f\n", celsius, fahr);
		celsius = celsius + step;
	}
}
