/*
 * Exercise 2-7
 *
 * Write a function invert(x, p, n) that returns x with the n bits that
 * begin at position p inverted (i.e., 1 changed into 0 and vice versa),
 * leaving the others unchanged.
 */
#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
	int x = 9713;	// 0010 0101 1111 0001
	printf("Result: %u\n", invert(x, 11, 4)); // 0010 1010 1111 0001 // p11 n4
	return 0;
}

unsigned invert(unsigned x, int p, int n)
{
	/*return ((~((x >> (p+1-n)) & ~(~0 << n)) & ~(~0 << n)) << (p+1-n)) |
	  x & ~(~0 << (p+1-n)) | (x >> (p+1)) << (p+1)*/;
	return x ^ ((~(~0<<n))<< p+1-n);
	//return (x ^ (((1 << (n)) - 1) << (p - n + 1)));
	//(((x >> (p+1-n)) & ~(~0 << n)) << (p+1-n))
	//(x >> (p+1)) << (p+1) //0010 0000 0000 0000
}
