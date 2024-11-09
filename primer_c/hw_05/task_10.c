#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int number = 0;
    bool isAscending = true;

    printf("Input an integer number: ");
    scanf("%d", &number);
    number = abs(number);

    /**
     * @details do-while используется на случай, если ввели 0.
     */
    int prevDigit = BASE_10;
    do {
        const int curDigit = number % BASE_10;
        if (prevDigit <= curDigit) {
            isAscending = false;
            break;
        }
        prevDigit = curDigit;
        number /= BASE_10;
    } while (number != 0);

    printf("\nAre the number's digits in ascending order: ");
    if (isAscending) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
