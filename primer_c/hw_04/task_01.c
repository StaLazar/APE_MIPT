#include "stdio.h"

int main(void) {
    int numbers[2] = {0, 0};
    int difference = 0;

    printf("Input 2 numbers:\n");
    scanf("%d %d", &numbers[0], &numbers[1]);

    difference = numbers[0] - numbers[1];

    printf("\nThe difference of 2 numbers:\n");
    printf("%d - %d = %d\n", numbers[0], numbers[1], difference);

    return 0;
}
