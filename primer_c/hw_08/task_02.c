#include <stdio.h>

/**
 * @brief Получить минимальный элемент массива.
 * @param array Массив элементов.
 * @param size Размер массива.
 * @return Минимальный элемент массива.
 */
int getMinOfArray(const int *array, const size_t size) {
    int min = array[0];
    for (size_t i = 0; i < size; ++i) {
        min = (array[i] < min) ? array[i] : min;
    }
    return min;
}

int main(void) {
    const size_t size = 5;
    int numArray[size];

    printf("Input a list of %ld integer numbers:\n", size);
    for (size_t i = 0; i < size; ++i) {
        scanf("%d", &numArray[i]);
    }

    const int min = getMinOfArray(numArray, size);
    printf("\nThe min of the list: %d\n", min);

    return 0;
}
