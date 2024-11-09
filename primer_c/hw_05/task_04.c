#include <stdio.h>

int main(void) {
    int number = 0;
    int digitCount = 0;

    printf("Input an integer number: ");
    scanf("%d", &number);

    /**
     * @details do-while используется на случай, если ввели 0.
     */
    const int base = 10;
    do {
        ++digitCount;
        number /= base;
    } while (number != 0);

    printf("\nIs there a 3-digit number: ");
    if (digitCount == 3) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
