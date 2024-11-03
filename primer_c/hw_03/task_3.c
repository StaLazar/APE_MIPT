#include "stdio.h"

int main(void) {
    int numbers[3] = {0, 0, 0};
    float average = 0;

    printf("Input 3 numbers:\n");
    scanf("%d %d %d", &numbers[0], &numbers[1], &numbers[2]);

    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    for (size_t i = 0; i < count; ++i) {
        average += numbers[i];
    }
    average /= count;

    printf("\nThe average of 3 numbers: %.2f\n", average);

    return 0;
}
