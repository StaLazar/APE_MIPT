#include <stdio.h>

#define BASE_10 10 //!< Основание десятичной системы счисления.

int main(void) {
    int number = 0;
    int sum = 0;
    const int targetSum = 10;

    printf("Input a natural number: ");
    scanf("%d", &number);

    const int lowerEdge = 1;
    if (number < lowerEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    while (number != 0) {
        sum += number % BASE_10;
        number /= BASE_10;
    }

    printf("\nIs the number's digits sum equal to %d: ", targetSum);
    if (sum == targetSum) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
