#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>


struct work {
    int a;
    int b;
    double x;
    double y;
    char *date;
    int group_index;
    char surname[64];
    char name[64];
    char middle_name[64];
};

int main(int argc, char *argv[]) {
    int a = 13;
    int b = 19;
    double x;
    double y;
    time_t raw_time;
    time(&raw_time);
    char *date = strtok(ctime(&raw_time), "\n");

    printf("Please, provide x: ");
    scanf("%lf", &x);

    if (x < 3.0) {
        y = a * x;
    } else if (x == 3.0) {
        y = pow(M_E, 2.0 * x);
    } else {
        y = log(a * b * x);
    }

    struct work my_lab = {a, b, x, y, date, 73, "Боярко", "Оксана", "Александровна"};

    FILE *final_file;
    final_file = fopen("file.txt", "wt");

    if (final_file != nullptr) {

        fprintf(final_file, "%s \n"
                        "|%30s"
                        "|%10s"
                        "|%10s"
                        "|%14s"
                        "|%12s"
                        "|%5s"
                        "|%5s"
                        "|%11s"
                        "|%11s| \n",
                "Our table with data:",
                "date",
                "Surname",
                "Name",
                "Middle name",
                "Group index",
                "A",
                "B",
                "x",
                "y");

        fprintf(final_file, "|%30s| %15s| %15s|%27s|%12.0d| %4.0d| %4.0d| %10.3lf| %10.3lf|\n",
                my_lab.date,
                my_lab.surname,
                my_lab.name,
                my_lab.middle_name,
                my_lab.group_index,
                my_lab.a,
                my_lab.b,
                my_lab.x,
                my_lab.y);

        fclose(final_file);
    }

    return 0;
}
