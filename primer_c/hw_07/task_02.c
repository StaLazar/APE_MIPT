#include <stdio.h>

/**
 * @brief Получить сумму натуральных чисел вплоть до заданного.
 * @warning Рекурсивная функция.
 * @param edgeNum Заданное число.
 * @return Сумма натуральных чисел вплоть до заданного.
 */
int getNaturalSum(const int edgeNum) {
    static const int lowerEdge = 1;
    if (edgeNum < lowerEdge) {
        return 0;
    }
    return edgeNum + getNaturalSum(edgeNum - 1);
}

int main(void) {
    int number = 0;
    const int lowerEdge = 1;
    int sum = 0;

    printf("Input a natural number: ");
    scanf("%d", &number);

    if (number < lowerEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    sum = getNaturalSum(number);
    printf("\nThe sum of natural numbers' list: %d\n", sum);

    return 0;
}
