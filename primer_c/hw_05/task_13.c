#include <stdio.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int number = 0;
    int evenCount = 0;
    int oddCount = 0;

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
        if (curDigit % 2 == 0) {
            ++evenCount;
        } else {
            ++oddCount;
        }
        number /= BASE_10;
    } while (number != 0);

    printf("\nThe amount of even number's digits: %d\n", evenCount);
    printf("The amount of odd number's digits: %d\n", oddCount);

    return 0;
}
