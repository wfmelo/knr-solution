/*
 * Exercise 3-1
 *
 * Our binary search makes two tests inside the loop, when one would suffice
 * (at the price of more tests outside).  Write a version with only one test
 * inside the loop and measure the difference in run-time.
 */

#include <stdio.h>

int binsearch(int x, int v[], int n);

int main()
{
	int v[10] = {3, 4, 5, 6, 8, 10, 12, 15, 18, 22};
		
	printf("%d\n", binsearch(15, v, 10));
	return 0;
}

/* benseach: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high && x != v[mid = (low + high) / 2]) {
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;

	}
	return (x == v[mid]) ? mid : -1;
}
