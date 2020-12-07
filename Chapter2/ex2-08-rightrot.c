/*
 * Exercise 2-8
 *
 * Write a function rightrot(x, n) that returns the value of the integer x
 * rotated to the right n bit positions.
 */
#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main()
{
	unsigned x = 9713;	// 0010 0101 1111 0001
	
	printf("%u\n", rightrot(x, 4));
	return 0;
}

unsigned rightrot(unsigned x, int n)
{
	int dec, max;
	unsigned int i, q;

	dec = x ; i = 0;
	max = 1;
	/* calculate number of bits */
	while (dec > 0) {
		dec = dec / 2;
		++i;
	}
	q = (i + 4 - 1) / 4; 	// round up
	q = (4 * q);
	/* calculate max bit */
	for(int j = 1; j <= q-1; ++j) {
		max *= 2;
	}
	//printf("%d\n", i);
	//printf("%d\n", max);
	/* rotate to the right by n bits position */
	for (int j = 0; j < n; ++j) {
		if (x & 0b0001 == 1) {
			x = (x >> 1) | max;
		}
		else
			x >>= 1;
	}
	return x; 
	// ~(~0U >> x) - rotate to the right in the end
}
