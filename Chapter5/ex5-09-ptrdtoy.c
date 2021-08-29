/* Exercise 5-9.
 *
 * Rewrite the routines day_of_year and month_day with pointers instead of
 * indexing.
 */

#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: calculating the day of the year by month and days */
int day_of_year(int year, int month, int day)
{
    char *p;
    int leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (p = daytab[leap]; p < (daytab[leap] + month); p++)
        day += *p;
    return day;
}

/* month_day: calculating month and date by day of the year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    char *p;
    int leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (p = daytab[leap]; yearday > *p; p++)
        yearday -= *p;
    *pmonth = (p - daytab[leap]);
    *pday = yearday;
}

int main(void)
{
    int day, m, d;
    char *p = daytab[1];

    printf("%d\n", p[2]);
    day = day_of_year(1988, 3, 1);
    printf("%d\n", day);
    month_day(1988, 61, &m, &d);
    printf("m = %d; d = %d\n", m, d);
    return 0;
}
