#include <stdio.h>

static char year_lookup[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char leap_lookup[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static char *daytab[] = {
    year_lookup,
    leap_lookup,
};

bool try_get_day_of_year(int year, int month, int day, int *out_day) {
    if (month < 1 || month > 12) {
        return false;
    }

    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    i = daytab[leap][month];
    if (day < 1 || day > i) {
        return false;
    }

    for (i = 1; i < month; ++i) {
        day += daytab[leap][i];
    }

    *out_day = day;
    return true;
}

bool try_get_month_day(int year, int yearday, int *out_month, int *out_day) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (leap) {
        if (yearday < 1 || yearday > 366) {
            return false;
        }
    } else {
        if (yearday < 1 || yearday > 365) {
            return false;
        }
    }

    for (i = 1; yearday > daytab[leap][i]; ++i) {
        yearday -= daytab[leap][i];
    }

    *out_month = i;
    *out_day = yearday;
    return true;
}

int main() {
    int month, day;
    bool success;

    if (try_get_day_of_year(1998, 03, 02, &day)) {
        printf("day: %i\n", day);
    } else {
        printf("error: invalid date");
    }

    if (try_get_day_of_year(1998, 13, 02, &day)) {
        printf("day: %i\n", day);
    } else {
        printf("error: invalid date\n");
    }

    if (try_get_day_of_year(1998, 03, 0, &day)) {
        printf("day: %i\n", day);
    } else {
        printf("error: invalid date\n");
    }

    if (try_get_month_day(1234, 42, &month, &day)) {
        printf("%i %i\n", month, day);
    } else {
        printf("error: invalid date\n");
    }

    if (try_get_month_day(1234, 366, &month, &day)) {
        printf("%i %i\n", month, day);
    } else {
        printf("error: invalid date\n");
    }

    if (try_get_month_day(4, 367, &month, &day)) {
        printf("%i %i\n", month, day);
    } else {
        printf("error: invalid date\n");
    }

    return 0;
}

