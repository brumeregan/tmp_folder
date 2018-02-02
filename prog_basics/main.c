#include <stdio.h>

int main() {
    int birth_year = 1988;
    int birth_month = 7;
    int birth_day = 15;
    int curr_year = 2017;
    int curr_month = 10;
    int curr_day = 24;
    int age_year;
    int age_days;
    int days = 30;

    if (curr_year > birth_year) {
        if (curr_month >= birth_month) {
            age_year = curr_year - birth_year;
            age_days = (curr_month - birth_month) * days + (days - birth_day) + curr_day;
        } else {
            age_year = curr_year - birth_year - 1;
            age_days = curr_month * days + curr_day;
        }
    }

    printf("%d years and %d days", age_year, age_days);

    return 0;
}
