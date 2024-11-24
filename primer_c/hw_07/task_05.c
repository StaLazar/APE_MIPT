#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Возвести число в заданную степень.
 * @warning Рекурсивная функция.
 * @param base Основание.
 * @param pow Степень.
 * @return Искомое число в заданной степени.
 */
int power(const int base, const int pow) {
    if (pow == 0) {
        return 1;
    }
    if (pow == 1) {
        return base;
    }
    return base * power(base, pow - 1);
}

int main(void) {
    int base = 0;
    int pow = 0;
    const int lowerEdge = 0;
    const int upperEdge = 100;

    printf("Input a base and a power: ");
    scanf("%d %d", &base, &pow);

    if (upperEdge < abs(base)) {
        printf("Interrupting: the base is out of range!\n");
        return 1;
    }

    if ((pow < lowerEdge) || (upperEdge < pow)) {
        printf("Interrupting: the power is out of range!\n");
        return 2;
    }

    int result = power(base, pow);
    printf("\n%d in power of %d: %d\n", base, pow, result);

    return 0;
}
