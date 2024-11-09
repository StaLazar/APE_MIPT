#include "stdio.h"

int main(void) {
    int numbers[3] = {0, 0, 0};
    int max = 0;

    printf("Input 3 numbers:\n");
    scanf("%d %d %d", &numbers[0], &numbers[1], &numbers[2]);

    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    max = numbers[0];
    for (size_t i = 0; i < count; ++i) {
        max = (max < numbers[i]) ? numbers[i] : max;
    }

    printf("\nThe max of 3 numbers: %d\n", max);

    return 0;
}
