#include <stdio.h>
#include <limits.h>

//! Размер квадратной матрицы.
#define SQ_MATRIX_SIZE 5

/**
 * @brief Заполнить квадратную матрицу значениями из консоли.
 * @param matrix Квадратная матрица для заполнения.
 */
void fillSquareMatrix(int matrix[SQ_MATRIX_SIZE][SQ_MATRIX_SIZE]) {
    printf("Input %d numbers:\n", SQ_MATRIX_SIZE * SQ_MATRIX_SIZE);
    for (size_t i = 0; i < SQ_MATRIX_SIZE; ++i) {
        for (size_t j = 0; j < SQ_MATRIX_SIZE; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

/**
 * @brief Получить среднее арифметическое главной диагонали матрицы.
 * @param matrix Матрица, для которой необходимо найти среднее арифметическое.
 * @return Среднее арифметическое главной диагонали матрицы.
 */
float getAverageOfMD(const int matrix[SQ_MATRIX_SIZE][SQ_MATRIX_SIZE]) {
    float result = 0.f;
    for (size_t i = 0; i < SQ_MATRIX_SIZE; ++i) {
        result += matrix[i][i];
    }
    result /= SQ_MATRIX_SIZE;
    return result;
}

/**
 * @brief Получить число магических элементов матрицы.
 * @details Магическим элементом считается положительное число, превышающее по величине
 * среднее арифметическое главной диагонали матрицы.
 * @param matrix Матрица, для которой необходимо получить число магических элементов.
 * @return Число магических элементов матрицы.
 */
int getMagicNumQuantity(const int matrix[SQ_MATRIX_SIZE][SQ_MATRIX_SIZE]) {
    int counter = 0;
    const float edgeValue = getAverageOfMD(matrix);
    for (size_t i = 0; i < SQ_MATRIX_SIZE; ++i) {
        for (size_t j = 0; j < SQ_MATRIX_SIZE; ++j) {
            if ((matrix[i][j] > 0) && (matrix[i][j] > edgeValue)) {
                ++counter;
            }
        }
    }
    return counter;
}

int main(void) {
    int matrix[SQ_MATRIX_SIZE][SQ_MATRIX_SIZE];
    fillSquareMatrix(matrix);

    const int counter = getMagicNumQuantity(matrix);

    printf("\nThe quantity of magic numbers: %d\n", counter);

    return 0;
}
