#include <stdio.h>
#include <math.h>

/**
 * @brief Получить член геометрической прогресии.
 * @param initial первый член прогрессии.
 * @param ratio знаменатель прогрессии.
 * @param number порядковый номер искомого члена прогрессии.
 * @return Член геометрической прогрессии.
 */
double getGeomRateMember(const int initial, const int ratio, const int number) {
    return initial * pow(ratio, number - 1);
}

int main(void) {
    int memberNum = 0;
    const int lowerEdge = 1;
    const int upperEdge = 64;

    printf("Input a natural number in range [%d; %d]: ", lowerEdge, upperEdge);
    scanf("%d", &memberNum);

    if ((memberNum < lowerEdge) || (memberNum > upperEdge)) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    const int initial = 1;
    const int ratio = 2;
    const double result = getGeomRateMember(initial, ratio, memberNum);
    printf("\nGeometric progression's member: %.0f\n", result);

    return 0;
}
