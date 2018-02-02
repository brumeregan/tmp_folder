#include <stdio.h>
#include <math.h>

#define A 11
#define B 17
// TODO  Здесь сделать свитч

int main(void) {
    double x, y;

    printf("Please, provide x: ");
    scanf("%lf", &x);

    if (x < 3.0) {
        y = A*x;
    } else if (x == 3.0) {
        y = pow(M_E, 2.0*x);
    } else {
        y = log(A*B*x);
    }

    printf("x = %.3lf \n", x);
    printf("y = %.3lf ", y);

    return 0;
}
