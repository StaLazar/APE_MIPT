#include "stdio.h"

int main(void) {
    int edgeNum = 0;
    const int lowerEdge = 1;
    const int upperEdge = 100;

    printf("Input a natural number not exceeding %d: ", upperEdge);
    scanf("%d", &edgeNum);

    if ((edgeNum < lowerEdge) || (edgeNum > upperEdge)) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    printf("\nNumber\tSquare\tCube\n");
    for (int number = lowerEdge; number <= edgeNum; ++number) {
        const int square = number * number;
        const int cube = square * number;
        printf("%d\t%d\t%d\n", number, square, cube);
    }

    return 0;
}
