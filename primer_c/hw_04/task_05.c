#include "stdio.h"

int main(void) {
    int numbers[5] = {0, 0, 0, 0, 0};
    int min = 0;

    printf("Input 5 numbers:\n");
    scanf("%d %d %d %d %d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4]);

    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    min = numbers[0];
    for (size_t i = 0; i < count; ++i) {
        min = (min > numbers[i]) ? numbers[i] : min;
    }

    printf("\nThe min of 5 numbers: %d\n", min);

    return 0;
}
