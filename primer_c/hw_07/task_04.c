#include <stdio.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

/**
 * @brief Напечатать через пробел цифры заданного числа.
 * @param num Число, цифры которого необходимо напечатать через пробел.
 */
void printNumDigits(const int num) {
    if (num == 0) {
        return;
    }
    printNumDigits(num / BASE_10);
    printf("%d ", num % BASE_10);
}

int main(void) {
    int number = 0;
    const int lowerEdge = 1;

    printf("Input a natural number: ");
    scanf("%d", &number);

    if (number < lowerEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    printf("\nThe list of number's digits:\n");
    printNumDigits(number);
    printf("\n");

    return 0;
}
