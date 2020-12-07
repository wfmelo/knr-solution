/*
 * Exercise 2-3
 *
 * Write the function htoi(s), which converts a string of hexadecimal digits
 * (including an optinal 0x or 0X) into its equivalent integer value.  The
 * allowable digits are 0 through 9, a through f, and A through F.
 */
#include <stdio.h>

int htoi(char s[]);

int main()
{
	char s[] = "0x2af";
	int n;
	
	htoi(s);
	return 0;
}

int htoi(char s[])
{
	int i, n, k;

	n = 0;
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
		for (i = 2; (s[i] >= '0' && s[i] <= '9') ||
				 (s[i] >= 'a' && s[i] <= 'f') ||
				 (s[i] >= 'A' && s[i] <= 'F'); ++i)
			if (s[i] >= '0' && s[i] <= '9')
				n = 16 * n + (s[i] - '0');
			else {
				if (s[i] == 'A' || s[i] == 'a')
					k = 10;
				else if (s[i] == 'B' || s[i] == 'b')
					k = 11;
				else if (s[i] == 'C' || s[i] == 'c')
					k = 12;
				else if (s[i] == 'D' || s[i] == 'd')
					k = 13;
				else if (s[i] == 'E' || s[i] == 'e')
					k = 14;
				else if (s[i] == 'F' || s[i] == 'f')
					k = 15;
				n = 16 * n + k;
			}
		printf("%d\n", n);
	}
	else
		printf("%s - Value must be in the format hex (0x or 0X)\n", s);
}
