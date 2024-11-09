#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int numbers[3] = {0, 0, 0};
    bool isAscending = true;

    printf("Input 3 numbers:\n");
    scanf("%d %d %d", &numbers[0], &numbers[1], &numbers[2]);

    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    for (size_t i = 0, j = i + 1; j < count; ++i, ++j) {
        if (numbers[i] >= numbers[j]) {
            isAscending = false;
            break;
        }
    }

    printf("\nThe numbers are in ascending order: ");
    isAscending ? printf("YES\n") : printf("NO\n");

    return 0;
}
