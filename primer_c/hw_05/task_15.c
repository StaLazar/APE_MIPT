#include <stdio.h>

int main(void) {
    int number = 0;
    int evenCount = 0;

    const int excludingNum = 0;
    printf("Input a list of integer numbers ending with %d: ", excludingNum);
    for (scanf("%d", &number); number != excludingNum;) {
        if (number % 2 == 0) {
            ++evenCount;
        }
        scanf("%d", &number);
    }

    printf("\nThe amount of even numbers: %d\n", evenCount);

    return 0;
}
