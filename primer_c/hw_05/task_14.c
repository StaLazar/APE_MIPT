#include <stdio.h>

int main(void) {
    int number = 0;
    int numCount = 0;

    const int excludingNum = 0;
    printf("Input a list of integer numbers: ");
    for (scanf("%d", &number); number != excludingNum; ++numCount) {
        scanf("%d", &number);
    }

    printf("\nThe amount of numbers: %d\n", numCount);

    return 0;
}
