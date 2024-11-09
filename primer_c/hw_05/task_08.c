#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int number = 0;
    const int targetDigit = 9;
    int targetDigitCount = 0;

    printf("Input an integer number: ");
    scanf("%d", &number);
    number = abs(number);

    /**
     * @details do-while используется на случай, если ввели 0.
     */
    do {
        const int curDigit = number % BASE_10;
        if (curDigit == targetDigit) {
            ++targetDigitCount;
        }
        number /= BASE_10;
    } while (number != 0);

    printf("\nIs there only one '%d': ", targetDigit);
    if (targetDigitCount == 1) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
