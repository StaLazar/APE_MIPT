#include "stdio.h"

int main(void) {
    int numbers[2] = {0, 0};

    printf("Input 2 numbers:\n");
    scanf("%d %d", &numbers[0], &numbers[1]);

    printf("\nThe numbers in ascending order:\n");
    (numbers[0] < numbers[1]) ? printf("%d %d\n", numbers[0], numbers[1]) :
                                printf("%d %d\n", numbers[1], numbers[0]);

    return 0;
}
