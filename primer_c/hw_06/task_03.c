#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.1416f

/**
 * @brief Перевести значение из градусов в радианы.
 * @param degrees Значение в градусах.
 * @return Значение в радианах.
 */
float degreesToRadians(const float degrees) {
    return degrees * PI / 180.f;
}

/**
 * @brief Найти факториал числа.
 * @param factor Натуральное число.
 * @return Факториал искомого числа.
 */
int factorial(const int factor) {
    int result = 1;

    for (int i = 1; i <= factor; ++i) {
        result *= i;
    }

    return result;
}

/**
 * @brief Найти синус угла с заданной точностью.
 * @param angle Угол в радианах.
 * @param precision Точность вычислений.
 * @return Синус искомого угла.
 */
float sinus(const float angle, const float precision) {
    float result = 0;
    float summand = 0;
    int power = 1;
    int index = 1;

    while (true) {
        summand = pow(angle, power) / factorial(power);
        if (summand < precision) {
            break;
        }
        if (index % 2 == 0) {
            summand *= -1.f;
        }
        result += summand;
        power += 2;
        ++index;
    }

    return result;
}

int main(void) {
    float angleDegrees = 0.f;
    const float lowerEdge = 0.f;
    const float upperEdge = 90.f;

    printf("Input the angle value in degrees in range [%0.f; %0.f]: ", lowerEdge, upperEdge);
    scanf("%f", &angleDegrees);

    if ((angleDegrees < lowerEdge) || (angleDegrees > upperEdge)) {
        printf("Interrupting: the angle value is out of range!\n");
        return 1;
    }

    const float result = sinus(degreesToRadians(angleDegrees), 0.001f);
    printf("\nThe sinus of %.3f degrees: %.3f\n", angleDegrees, result);

    return 0;
}
