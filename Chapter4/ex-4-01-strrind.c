/* Exercise 4-1
 *
 * Write a function strrindex(s, t), which returns the position of the 
 * rightmost occurence of t in s or -1 if there is none.
 */
#include <stdio.h>

int strrindex(char source[], char searchfor[]);

// find all strings containing a given pattern
int main()
{
	char parent[] = "Re-mould it nearer to the Heart's Desire!";
	char child[] = "ea";
	int i;

	i = strrindex(parent, child);
	printf("%d\n",i);
	return 0;
}

/* strindex: returns the index of the right occurrence of
 * string t in s, -1 if absent */
int strrindex(char s[], char t[])
{
	int i, j, k, l = -1;

	for (i = 0; s[i] != '\0'; i++) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			l = i;
	}
	return l;
}
