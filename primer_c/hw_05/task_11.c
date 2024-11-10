#include <stdio.h>
#include <math.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int originalNum = 0;
    int reverseNum = 0;

    printf("Input a non-negative integer number: ");
    scanf("%d", &originalNum);

    const int lowerEdge = 0;
    if (originalNum < lowerEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    int digitCount = 0;
    int temporaryNum = originalNum;
    /**
     * @details do-while используется на случай, если ввели 0.
     */
    do {
        ++digitCount;
        temporaryNum /= BASE_10;
    } while (temporaryNum != 0);

    for (int power = digitCount - 1; power >= 0; --power) {
        const int curDigit = originalNum % BASE_10;
        reverseNum += curDigit * pow(BASE_10, power);
        originalNum /= BASE_10;
    }

    printf("\nThe reverse number: %d\n", reverseNum);

    return 0;
}
