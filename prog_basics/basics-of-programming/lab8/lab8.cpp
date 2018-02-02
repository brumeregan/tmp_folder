#include <cstdio>
#include <ctime>
#include <cmath>

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

int main(int argc, char* argv[]) {
    int a = 13;
    int b = 19;
    double x;
    double y;
    time_t raw_time;
    time(&raw_time);
    char *date = ctime(&raw_time);

    printf("Please, provide x: ");
    scanf("%lf", &x);

    if (x < 3.0) {
        y = a*x;
    } else if (x == 3.0) {
        y = pow(M_E, 2.0*x);
    } else {
        y = log(a*b*x);
    }

    struct work my_lab = { a, b, x, y, date, 73, "Боярко", "Оксана", "Александровна" };

    printf("This is our structure:\n"
                   "date: %s"
                   "Surname: %s \n"
                   "Name: %s \n"
                   "Middle name: %s\n"
                   "Group index: %.0d \n"
                   "A: %d \n"
                   "B: %d \n"
                   "x: %.3f \n"
                   "y: %.3f\n",
           my_lab.date,
           my_lab.surname,
           my_lab.name,
           my_lab.middle_name,
           my_lab.group_index,
           my_lab.a,
           my_lab.b,
           my_lab.x,
           my_lab.y);

    return 0;
}
