#include <stdio.h>

/**
 * @brief Напечатать ряд натуральных чисел вплоть до заданного.
 * @warning Рекурсивная функция.
 * @param edgeNum Заданное число, вплоть до которого будет идти печать.
 */
void printNaturalNumbers(const int edgeNum) {
    static const int lowerEdge = 1;
    if (edgeNum < lowerEdge) {
        return;
    }
    printNaturalNumbers(edgeNum - 1);
    printf("%d ", edgeNum);
}

int main(void) {
    int number = 0;
    const int lowerEdge = 1;

    printf("Input a natural number: ");
    scanf("%d", &number);

    if (number < lowerEdge) {
        printf("Interrupting: the number is out of range!\n");
        return 1;
    }

    printf("\nThe list of natural numbers:\n");
    printNaturalNumbers(number);
    printf("\n");

    return 0;
}
