#include <stdio.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int number = 0;
    int sum = 0;

    printf("Input a positive integer number: ");
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
        sum += number % BASE_10;
        number /= BASE_10;
    } while (number != 0);

    printf("\nThe sum of number's digits: %d\n", sum);

    return 0;
}
