/*
 * Exercise 2-9
 *
 * In a two's complement number system, x &= (x-1) deletes the rightmost
 * 1-bit in x.  Explain Why.  Use this observation to write a faster version
 * of bitcount. *
 */
#include <stdio.h>

int bitcount(unsigned x);

int main()
{
	unsigned x = 9742;
	printf("%u\n", x);
	printf("%u\n", bitcount(x));
	return 0;
}

int bitcount(unsigned x)
{
	int b = 0;

	while (x != 0) {
		x &= x - 1;
		++b;
	}
	return b;
}
