#include <stdio.h>

/**
 * @brief Инвертировать элементы массива в заданном диапазоне индексов.
 * @param array Массив элементов.
 * @param begin Индекс начального элемента инверсии.
 * @param end Индекс конечного элемента инверсии.
 */
void reverseArray(int *array, size_t begin, size_t end) {
    while (begin < end) {
        int temp = array[begin];
        array[begin] = array[end];
        array[end] = temp;
        ++begin;
        --end;
    }
}

/**
 * @brief Выполнить циклический сдвиг массива вправо на заданную величину.
 * @param array Массив элементов.
 * @param size Размер массива.
 * @param shift Величина сдвига.
 */
void shiftArrayToRight(int *array, const size_t size, size_t shift) {
    shift %= size;
    reverseArray(array, 0, size - 1);
    reverseArray(array, 0, shift - 1);
    reverseArray(array, shift, size - 1);
}

/**
 * @brief Распечатать элементы массива в строку.
 * @param array Массив элементов.
 * @param size Размер массива.
 */
void printArray(const int *array, const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
}

int main(void) {
    const size_t size = 10;
    int numArray[size];

    printf("Input a list of %ld integer numbers:\n", size);
    for (size_t i = 0; i < size; ++i) {
        scanf("%d", &numArray[i]);
    }

    const int shift = 1;
    shiftArrayToRight(numArray, size, shift);

    printf("\nThe list, shifted to the right by %d element(s):\n", shift);
    printArray(numArray, size);
    printf("\n");

    return 0;
}
