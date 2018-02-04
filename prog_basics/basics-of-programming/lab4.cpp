#include <stdio.h>
#include <math.h>

#define A 11
#define B 17

int main(void) {
    double x, y;
    int choice;
    printf("Please, choose equation: 1, 2, 3 ");

    scanf("%d", &choice);
    printf("\nPlease, type x: ");
    scanf("%lf", &x);

    switch(choice) {
        case 1: {
            if (x < 3.0) {
                y = A*x;
            } else if (x == 3.0) {
                y = pow(M_E, 2.0*x);
            } else {
                y = log(A*B*x);
            }
            break;
        }

        case 2: {
            y = (B*A)*sqrt(A*x*log10(A + x)) + pow(M_E, (A*x));
            break;
        }

        case 3: {
            double power = pow((x - 0.5), 3);
            y = pow(M_E, -power);
            break;
        }

        default: {
            printf("Please, provide appropriate choice. \n");
            return 0;
        }
    }
    putchar('\n');;

    printf("x = %.4f\n", x);
    printf("y = %.4f \n", y);

    return 0;
}
