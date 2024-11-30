#include <stdio.h>

/**
 * @brief Получить среднее арифметическое всех элементов массива.
 * @param array Массив элементов.
 * @param size Размер массива.
 * @return Среднее арифметическое всех элементов массива.
 */
float getAverageOfArray(const int *array, const size_t size) {
    float average = 0.f;
    for (size_t i = 0; i < size; ++i) {
        average += array[i];
    }
    average /= size;
    return average;
}

int main(void) {
    const size_t size = 5;
    int numArray[size];
    const int lowerEdge = 0;

    printf("Input a list of %ld natural numbers:\n", size);
    for (size_t i = 0; i < size; ++i) {
        scanf("%d", &numArray[i]);
        if (numArray[i] < lowerEdge) {
            printf("Interrupting: the number is out of range!\n");
            return 1;
        }
    }

    const float average = getAverageOfArray(numArray, size);
    printf("\nThe average of the list: %.3f\n", average);

    return 0;
}
