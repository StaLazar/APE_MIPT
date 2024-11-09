#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int number = 0;
    bool isIdentical = false;

    printf("Input an integer number: ");
    scanf("%d", &number);

    /**
     * @details do-while используется на случай, если ввели 0.
     */
    const int base = 10;
    int prevDigit = 10;
    do {
        const int curDigit = number % base;
        if (prevDigit == curDigit) {
            isIdentical = true;
            break;
        }
        prevDigit = curDigit;
        number /= base;
    } while (number != 0);

    printf("\nAre there any identical digits standing side by side: ");
    if (isIdentical) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
