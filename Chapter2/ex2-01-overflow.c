/*
 * Exercise 2-1
 *
 * Write a program to determine the ranges of char, short, int, and long
 * variables, both signed an unsigned, by printing appropriate values from
 * standard headers and by direct computation.  Harder if you compute them:
 * determine the ranges of the various floating-point types.
*/
#include <stdio.h>


long pow2(int val)
{
	long int pow;
	
	pow = 1;
	for(int i = 0; i < val; ++i)
		pow *= 2;
	return pow - 1; 
}

double pow10p(int val)
{
	double pow;
	
	pow = 1;
	for(int i = 0; i < val; ++i)
		pow *= 10;
	return pow; 
}

double pow10n(int val)
{
	double pow;
	
	pow = 1;
	for(int i = 0; i < val; ++i)
		pow /= 10;
	return pow; 
}

int main()
{
	int CHAR_BIT, INT_BIT, SHRT_BIT, LONG_BIT;
	int SCHAR_MIN, SCHAR_MAX, UCHAR_MAX;
	long INT_MIN, INT_MAX, UINT_MAX;
	int SHRT_MIN, SHRT_MAX, USHRT_MAX;
	long LONG_MIN, LONG_MAX, ULONG_MAX;
	float FLT_MIN, FLT_MAX;
	double DBL_MIN, DBL_MAX;
	int FLT_BIT, DBL_BIT;

	/* char */
	CHAR_BIT = 8;
	SCHAR_MAX = pow2(CHAR_BIT)/2;
	SCHAR_MIN = -SCHAR_MAX;
	UCHAR_MAX = pow2(CHAR_BIT);
	
	/* int */
	INT_BIT = 16;
	INT_MAX = pow2(INT_BIT)/2;
	INT_MIN = -INT_MAX;
	UINT_MAX = pow2(INT_BIT);

	/* short */
	SHRT_BIT = 16;
	SHRT_MAX = pow2(SHRT_BIT)/2;
	SHRT_MIN = -SHRT_MAX;
	USHRT_MAX = pow2(SHRT_BIT);

	/* long */
	LONG_BIT = 32;
	LONG_MAX = pow2(LONG_BIT)/2;
	LONG_MIN = -LONG_MAX;
	ULONG_MAX = pow2(LONG_BIT);

	/* float */
	FLT_BIT = 37;
	FLT_MAX = pow10p(FLT_BIT);
	FLT_MIN = pow10n(FLT_BIT);

	/* double*/
	DBL_BIT = 37;
	DBL_MAX = pow10p(DBL_BIT);
	DBL_MIN = pow10n(DBL_BIT);
	
	printf("signed char: min(%d) - max(%d)\n", SCHAR_MIN, SCHAR_MAX);
	printf("unsigned char: min(%d) - max(%d)\n", 0, UCHAR_MAX);
	printf("signed int: min(%ld) - max(%ld)\n", INT_MIN, INT_MAX);
	printf("unsigned int: min(%d) - max(%ld)\n", 0, UINT_MAX);
	printf("signed short: min(%d) - max(%d)\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short: min(%d) - max(%d)\n", 0, USHRT_MAX);
	printf("signed long: min(%ld) - max(%ld)\n", LONG_MIN, LONG_MAX);
	printf("unsigned long: min(%d) - max(%ld)\n", 0, ULONG_MAX);
	printf("float: min(%e) - max(%e)\n", FLT_MIN, FLT_MAX);
	printf("double: min(%e) - max(%e)\n", DBL_MIN, DBL_MAX);
	
	return 0;
}
