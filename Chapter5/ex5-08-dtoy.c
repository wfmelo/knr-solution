/* Exercise 5-8.
 * 
 * There is no error checking in day_of_year or month_day.
 * Remedy this defect.
 */
#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: calculating the day of the year by month and days */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (year < 1 || month < 1 || month > 12)
        return -1;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (day < 1 || day > daytab[leap][month])
        return -1;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: calculating month and date by day of the year  */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    if (year < 1 || yearday < 1 || yearday > 366) {
        *pmonth = -1;
        *pday = -1;
        return ;
    }
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; i <= 12 && yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
    }
    if (i > 12 && yearday) {
        *pmonth = -1;
        *pday = -1;
    } else  {
        *pmonth = i;
        *pday = yearday;
    }
    
}

int main(void)
{
    int day, m, d;

    day = day_of_year(1988, 3, 1);
    printf("%d\n", day);
    month_day(1700, 366, &m, &d);
    printf("m = %d; d = %d\n", m, d);
    return 0;
}
