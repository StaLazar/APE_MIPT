#include <stdio.h>
#include <math.h>

/**
 * @brief Перевести целое число из десятичной системы счисления в произвольную.
 * @param number Конвертируемое целое число в десятичной системе счисления.
 * @param base Основание системы счисления, в которую производится перевод.
 * @return Число в искомой системе счисления.
 */
int convertFromDecToAny(int number, int base) {
    int result = 0;
    const int posBase = 10;
    int posPower = 0;

    while (number >= base) {
        result += (number % base) * pow(posBase, posPower);
        number /= base;
        ++posPower;
    }
    result += number * pow(posBase, posPower);

    return result;
}

int main(void) {
    int number = 0;
    const int lowerNumberEdge = 0;
    int base = 0;
    const int lowerBaseEdge = 2;
    const int upperBaseEdge = 9;

    printf("Input a natural number greater than %d: ", lowerNumberEdge);
    scanf("%d", &number);

    if (number < lowerNumberEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    printf("Input new number's base in range [%d; %d]: ", lowerBaseEdge, upperBaseEdge);
    scanf("%d", &base);

    if ((base < lowerBaseEdge) || (base > upperBaseEdge)) {
        printf("Interrupting: the base is out of range!\n");
        return 2;
    }

    const int result = convertFromDecToAny(number, base);
    printf("\nThe number in new system: %d\n", result);

    return 0;
}
