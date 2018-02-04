#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    double y;
    double x = strtod(argv[1], NULL);
    double a = strtod(argv[2], NULL);
    double b = strtod(argv[3], NULL);

    if (argc == 4) {
        y = (log10(a + pow(x, 2)) - sqrt(b*x))/(tan(b*x) + pow(abs(a + x), 1/5.0));
        printf("x=%.3f, a=%.3f, b=%.3f, y = %.3f \n", x, a, b, y);
    } else {
        printf("Not enough variables!");
    }

    return 0;
}


