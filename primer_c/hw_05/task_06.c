#include <stdio.h>
#include <stdbool.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int number = 0;
    bool isIdentical = false;

    printf("Input an integer number: ");
    scanf("%d", &number);

    /**
     * @details do-while используется на случай, если ввели 0.
     */
    int prevDigit = 10;
    do {
        const int curDigit = number % BASE_10;
        if (prevDigit == curDigit) {
            isIdentical = true;
            break;
        }
        prevDigit = curDigit;
        number /= BASE_10;
    } while (number != 0);

    printf("\nAre there any identical digits standing side by side: ");
    if (isIdentical) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
