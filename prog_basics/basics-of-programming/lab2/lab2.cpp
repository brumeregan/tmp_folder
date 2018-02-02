#include <stdio.h>

int main(void) {
    char title[13] = "Cloud Atlas";
    int year = 2012;
    float budget = 128.5;
    float income = 130.5;

    printf("-----------------------------------Random film-----------------------------\n");
    printf("|%-12s | %13s | %15s | %20s ) |\n", "Title", "Released year", "Budget (million)", "Box office, (million");
    printf("|%-12s | %-13d | %16.2f | %23.2f| \n", title, year, budget, income);
    printf("--------------------------------This is the end----------------------------\n");

    return 0;
}
