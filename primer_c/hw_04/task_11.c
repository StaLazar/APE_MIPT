#include <stdio.h>

int main(void) {
    int numbers[2] = {0, 0};

    printf("Input 2 numbers:\n");
    scanf("%d %d", &numbers[0], &numbers[1]);

    printf("\nThe comparison result: ");
    if (numbers[0] > numbers[1]) {
        printf("above\n");
    } else if (numbers[0] < numbers[1]) {
        printf("less\n");
    } else {
        printf("equal\n");
    }

    return 0;
}
