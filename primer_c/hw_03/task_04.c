#include <stdio.h>

int main(void) {
    int number = 0;
    int sum = 0;

    printf("Input 3-digit number: ");
    scanf("%d", &number);

    const int lowerEdge = 100;
    const int upperEdge = 999;
    if ((number < lowerEdge) || (number > upperEdge)) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    const int base = 10;
    while (number != 0) {
        sum += number % base;
        number /= base;
    }

    printf("\nThe sum of number's digits: %d\n", sum);

    return 0;
}
