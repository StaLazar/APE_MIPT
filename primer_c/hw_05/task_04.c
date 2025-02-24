#include <stdio.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int number = 0;
    int digitCount = 0;

    printf("Input an integer number: ");
    scanf("%d", &number);

    /**
     * @details do-while используется на случай, если ввели 0.
     */
    do {
        ++digitCount;
        number /= BASE_10;
    } while (number != 0);

    printf("\nIs there a 3-digit number: ");
    if (digitCount == 3) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
