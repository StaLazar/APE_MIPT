#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int number = 0;
    bool isPrimeNumber = true;

    printf("Input a natural number: ");
    scanf("%d", &number);

    const int lowerEdge = 1;
    if (number < lowerEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    if (number == 1) {
        isPrimeNumber = false;
    }
    for (int divisor = 2; divisor < number; ++divisor) {
        if (number % divisor == 0) {
            isPrimeNumber = false;
            break;
        }
    }

    printf("\nIs there a prime number: ");
    if (isPrimeNumber) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
