#include <stdio.h>

/**
 * @brief Геометрическая точка с целочисленными координатами.
 */
struct point {
    int x;
    int y;
};

int main(void) {
    struct point points[2] = {{0, 0}, {0, 0}};
    float angularCoef = 0.f;
    float yAxisCoef = 0.f;

    printf("Input the coordinates of 2 points in the following format: X1 Y1 X2 Y2\n");
    scanf("%d %d %d %d", &points[0].x, &points[0].y, &points[1].x, &points[1].y);

    angularCoef = (float)(points[1].y - points[0].y) / (float)(points[1].x - points[0].x);
    yAxisCoef = points[0].y - angularCoef * points[0].x;

    if (yAxisCoef > 0) {
        printf("\nStraight line equation: Y = %.2f * X + %.2f\n", angularCoef, yAxisCoef);
    } else if (yAxisCoef < 0) {
        printf("\nStraight line equation: Y = %.2f * X - %.2f\n", angularCoef, (-1.f) * yAxisCoef);
    } else {
        printf("\nStraight line equation: Y = %.2f * X\n", angularCoef);
    }

    return 0;
}
