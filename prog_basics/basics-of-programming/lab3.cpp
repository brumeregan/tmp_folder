#include <stdio.h>
#include <math.h>

#define A 2
#define B 42

// TODO поменять с 4

int main(void) {

    double x, y;
    printf("Please, type x: ");
    scanf("%lf", &x);
    y = (B*A)*sqrt(A*x*log10(A + x)) + pow(M_E, (A*x));
    putchar('\n');
    printf("x = %.4f\n", x);
    printf("y = %.4f \n", y);
    putchar('\n');

    return 0;
}
