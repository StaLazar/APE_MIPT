#include "algorithm.h"
#include "common.h"
#include <stdio.h>

int main() {
    const float precision = 0.001F;

    roots[0] = getRoot(rootScopes[0], f, h, precision);
    printf("root #1 = %f\n", roots[0]);
    roots[1] = getRoot(rootScopes[1], g, h, precision);
    printf("root #2 = %f\n", roots[1]);
    roots[2] = getRoot(rootScopes[2], f, h, precision);
    printf("root #3 = %f\n", roots[2]);
    roots[3] = getRoot(rootScopes[3], g, h, precision);
    printf("root #4 = %f\n", roots[3]);
    roots[4] = getRoot(rootScopes[4], f, g, precision);
    printf("root #5 = %f\n", roots[4]);

    const float_pair firstScope = {roots[0], roots[1]};
    const float_pair secondScope = {roots[1], roots[4]};
    float square = 0.F;
    square += getSquare(firstScope, f, h, precision);
    square += getSquare(secondScope, f, g, precision);

    printf("square = %f\n", square);

    return 0;
}
