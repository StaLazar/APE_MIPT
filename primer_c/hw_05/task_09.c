#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int number = 0;
    bool isEven = true;

    printf("Input an integer number: ");
    scanf("%d", &number);
    number = abs(number);

    /**
     * @details do-while используется на случай, если ввели 0.
     */
    do {
        const int curDigit = number % BASE_10;
        if (curDigit % 2 == 1) {
            isEven = false;
            break;
        }
        number /= BASE_10;
    } while (number != 0);

    printf("\nAre all the number's digits even: ");
    if (isEven) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
