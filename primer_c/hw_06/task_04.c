#include <stdio.h>
#include <stdbool.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

/**
 * @brief Определить, является ли число магическим.
 * @details Число считается магическим, если сумма его цифр равна произведению.
 * @param number Натуральное число.
 * @return true - число магическое, false - иначе.
 */
bool isMagicNumber(int number) {
    int sum = 0;
    int product = 1;

    do {
        sum += number % BASE_10;
        product *= number % BASE_10;
        number /= BASE_10;
    } while (number != 0);

    if (sum == product) {
        return true;
    }
    return false;
}

int main(void) {
    int number = 0;
    const int lowerEdge = 0;

    printf("Input a natural number: ");
    scanf("%d", &number);

    if (number < lowerEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    printf("The number is magic: ");
    if (isMagicNumber(number)) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
