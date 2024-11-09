#include <stdio.h>

int main(void) {
    int sides[3] = {0, 0, 0};

    printf("Input the triangle's potential sides:\n");
    scanf("%d %d %d", &sides[0], &sides[1], &sides[2]);

    printf("\nIs there a triangle: ");
    if ((sides[0] + sides[1] > sides[2]) &&
            (sides[1] + sides[2] > sides[0]) &&
            (sides[2] + sides[0] > sides[1])) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    return 0;
}
