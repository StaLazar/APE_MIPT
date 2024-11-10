#include <stdio.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int number = 0;
    int minDigit = BASE_10;
    int maxDigit = BASE_10 - BASE_10 - 1;

    printf("Input a non-negative integer number: ");
    scanf("%d", &number);

    const int lowerEdge = 0;
    if (number < lowerEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    /**
     * @details do-while используется на случай, если ввели 0.
     */
    do {
        const int curDigit = number % BASE_10;
        minDigit = (curDigit < minDigit) ? curDigit : minDigit;
        maxDigit = (curDigit > maxDigit) ? curDigit : maxDigit;
        number /= BASE_10;
    } while (number != 0);

    printf("\nThe min number's digit: %d\n", minDigit);
    printf("The max number's digit: %d\n", maxDigit);

    return 0;
}
