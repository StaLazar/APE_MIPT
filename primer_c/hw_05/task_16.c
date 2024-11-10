#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int numbers[2] = {0, 0};

    printf("Input 2 natural numbers: ");
    scanf("%d %d", &numbers[0], &numbers[1]);

    const int lowerEdge = 1;
    if ((numbers[0] < lowerEdge) || (numbers[1] < lowerEdge)) {
        printf("Interrupting: the numbers are out of range!\n");
        return 1;
    }

    while ((numbers[0] != 0) && (numbers[1] != 0)) {
        if (numbers[0] > numbers[1]) {
            numbers[0] %= numbers[1];
        } else {
            numbers[1] %= numbers[0];
        }
    }
    const int gcd = numbers[0] + numbers[1];

    printf("\nThe greatest common divisor of numbers: %d\n", gcd);

    return 0;
}
