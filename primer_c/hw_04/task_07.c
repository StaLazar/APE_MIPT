#include <stdio.h>

int main(void) {
    int number = 0;
    int maxDigit = 0;

    printf("Input 3-digit number: ");
    scanf("%d", &number);

    const int lowerEdge = 100;
    const int upperEdge = 999;
    if ((number < lowerEdge) || (upperEdge < number)) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    const int base = 10;
    while (number != 0) {
        const int currentDigit = number % base;
        maxDigit = (currentDigit > maxDigit) ? currentDigit : maxDigit;
        number /= base;
    }

    printf("\nThe max of number's digits: %d\n", maxDigit);

    return 0;
}
