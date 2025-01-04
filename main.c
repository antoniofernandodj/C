#include <complex.h>
#include <math.h>
#include <stdio.h>


int main() {

    for (float x = 0.0; x <= 3.15; x += 0.1) {
        printf("%f\n", sinf(x));

    };

    return 0;
}
