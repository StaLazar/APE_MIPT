#include "algorithm.h"
#include <stdio.h>
#include "math.h"

float getRoot(float_pair scope, function *first, function *second, const float precision) {
    while (fabsf(scope.first - scope.second) > precision) {
        scope.first = scope.second -
            (scope.second - scope.first) * getDifference(first, second, scope.second) /
            (getDifference(first, second, scope.second) - getDifference(first, second, scope.first));
        scope.second = scope.first -
            (scope.first - scope.second) * getDifference(first, second, scope.first) /
            (getDifference(first, second, scope.first) - getDifference(first, second, scope.second));
    }
    return scope.second;
}

float getSquare(float_pair scope, function *upper, function *lower, const float precision) {
    const float height = (scope.second - scope.first) * precision;
    float square = 0.F;
    for (float x = scope.first; x < scope.second; x += height) {
        square += 0.5F * height *
            (getDifference(upper, lower, x) + getDifference(upper, lower, x + height));
    }
    return square;
}
