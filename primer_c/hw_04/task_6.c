#include "stdio.h"

int main(void) {
    int numbers[5] = {0, 0, 0, 0, 0};
    int min = 0;
    int max = 0;
    int sum = 0;

    printf("Input 5 numbers:\n");
    scanf("%d %d %d %d %d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4]);

    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    min = max = numbers[0];
    for (size_t i = 0; i < count; ++i) {
        min = (min > numbers[i]) ? numbers[i] : min;
        max = (max < numbers[i]) ? numbers[i] : max;
    }
    sum = min + max;

    printf("\nThe sum of min and max: %d\n", sum);

    return 0;
}
