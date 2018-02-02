#include <stdio.h>
#include <math.h>

#define A 11
#define B 17

double eq(double x) {
    double y;

    if (x < 3.0) {
        y = A*x;
    } else if (x == 3.0) {
        y = pow(M_E, 2.0*x);
    } else {
        y = log(A*B*x);
    }

    printf("x = %.3lf \n", x);
    printf("y = %.3lf \n", y);

    return 0;
}
