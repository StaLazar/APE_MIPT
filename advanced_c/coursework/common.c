#include "common.h"
#include <stdio.h>
#include "math.h"

float_pair rootScopes[ROOTS_COUNT] = {
    {-7.F, -5.F}, {-1.F, -0.1F}, {0.1F, 1.F}, {3.F, 3.5F}, {3.5F, 4.F}
};

float roots[ROOTS_COUNT] = {};

float getDifference(function *first, function *second, const float x) {
    return first(x) - second(x);
}

float f(const float x) {
    return 0.6F * x + 3.F;
}

float g(const float x) {
    return powf((x - 2.F), 3.F) - 1.F;
}

float h(const float x) {
    if (x == 0.F) {
        printf("Division by 0 is unacceptable!\n");
        return x;
    }
    return 3.F / x;
}
