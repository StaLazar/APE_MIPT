#include "stdio.h"

int main(void) {
    int summands[3] = {0, 0, 0};
    int sum = 0;

    printf("Input 3 numbers:\n");
    scanf("%d %d %d", &summands[0], &summands[1], &summands[2]);

    const size_t count = sizeof(summands) / sizeof(summands[0]);
    for (size_t i = 0; i < count; ++i) {
        sum += summands[i];
    }

    printf("\nThe sum of 3 numbers:\n");
    printf("%d + %d + %d = %d\n", summands[0], summands[1], summands[2], sum);

    return 0;
}
