#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int number = 0;
    bool isIdentical = false;
    bool digitFlags[BASE_10];
    for (size_t i = 0; i < BASE_10; ++i) {
        digitFlags[i] = false;
    }

    printf("Input an integer number: ");
    scanf("%d", &number);
    number = abs(number);

    /**
     * @details do-while используется на случай, если ввели 0.
     */
    do {
        const int curDigit = number % BASE_10;
        if (digitFlags[curDigit]) {
            isIdentical = true;
            break;
        }
        digitFlags[curDigit] = true;
        number /= BASE_10;
    } while (number != 0);

    printf("\nAre there any identical digits: ");
    if (isIdentical) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
