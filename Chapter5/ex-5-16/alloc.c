#define ALLOCSIZE 10000    /* available memory */

static char allocbuf[ALLOCSIZE]; /* memory buffer for  alloc */
static char *allocp = allocbuf;  /* next free position */

char *alloc(int n)    /* returns a pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* there is a place */
        allocp += n;
        return allocp - n;    /* old pointer */
    } else /* not enough buffer spac */
        return 0;
}

void afreee(char *p)    /* freeing memory at address p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
