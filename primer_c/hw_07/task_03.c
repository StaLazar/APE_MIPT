#include <stdio.h>

/**
 * @brief Распечатать число count раз.
 * @warning Рекурсивная функция.
 * @param num Число для печати.
 * @param count Количество итераций печати.
 */
void printNumber(const int num, const int count) {
    if (count == 0) {
        return;
    }
    printNumber(num, count - 1);
    printf("%d ", num);
}

/**
 * @brief Распечатать первые total членов последовательности.
 * @details Последовательность имеет вид: 1, 2, 2, 3, 3, 3, ...
 * @param total Количество членов последовательности для печати.
 */
void printSequence(const int total) {
    printf("\nThe list of first %d sequence's element(s):\n", total);
    for (int num = 1, amount = 0; amount < total; ++num) {
        const int freeSpace = total - amount;
        const int count = (num > freeSpace) ? freeSpace : num;
        printNumber(num, count);
        amount += count;
    }
    printf("\n");
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

    printSequence(number);

    return 0;
}
