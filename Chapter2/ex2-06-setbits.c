/*
 * Exercise 2-6
 *
 * Write a function setbits (x, p, n, y) that returns x with the n bits that
 * begin at position p set to the right most n bits of y, leaving the other
 * bits unchanged.
 */
#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
	int x = 9713;	// 0010 0101 1111 0001
	int y = 3500;   // 0000 1101 1010 1100

	// expecting 0010 1100 1111 0001 - 11761
	printf("Result: %d\n", setbits(x,6,2,y));
	printf("Result: 0x%x\n", setbits(0xB5, 5, 3, 0x2B)); // 0x9d
	printf("Result: %u\n", setbits(170, 4, 3, 7)); // 190
	printf("Result: %u\n", setbits(4910, 6, 2, 3)); // 4974
	
	return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	return (((x >> (p+1-n)) & (~0 << n) | y & ~(~0 << n)) << (p+1-n)) |
		(x & ~(~0 << p+1-n));
	//(x >> (p+1-n)) & (~0 << n)
	//((x >> (p+1-n)) & (~0 << n) | y & ~(~0 << n)) << (p+1-n)
}	//x & ~(~0 << p+1-n)
