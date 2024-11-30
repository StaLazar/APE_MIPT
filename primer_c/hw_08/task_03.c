#include <stdio.h>

/**
 * @brief Получить сумму положительных элементов массива.
 * @param array Массив элементов.
 * @param size Размер массива.
 * @return Сумма положительных элементов массива.
 */
int getPositiveSumOfArray(const int *array, const size_t size) {
    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += (array[i] > 0) ? array[i] : 0;
    }
    return sum;
}

int main(void) {
    const size_t size = 10;
    int numArray[size];

    printf("Input a list of %ld integer numbers:\n", size);
    for (size_t i = 0; i < size; ++i) {
        scanf("%d", &numArray[i]);
    }

    const int positiveSum = getPositiveSumOfArray(numArray, size);
    printf("\nThe sum of positive list's elements: %d\n", positiveSum);

    return 0;
}
