#include <stdio.h>
#include <limits.h>

//! Размер квадратной матрицы.
#define SQ_MATRIX_SIZE 10

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
 * @brief Получить сумму максимумов каждой строки матрицы.
 * @param matrix Матрица, для которой необходимо определить сумму.
 * @return Сумма максимумов каждой строки матрицы.
 */
int getSumOfMatrixMax(const int matrix[SQ_MATRIX_SIZE][SQ_MATRIX_SIZE]) {
    int result = 0;
    for (size_t i = 0; i < SQ_MATRIX_SIZE; ++i) {
        int max = INT_MIN;
        for (size_t j = 0; j < SQ_MATRIX_SIZE; ++j) {
            max = (matrix[i][j] > max) ? matrix[i][j] : max;
        }
        result += max;
    }
    return result;
}

int main(void) {
    int matrix[SQ_MATRIX_SIZE][SQ_MATRIX_SIZE];
    fillSquareMatrix(matrix);

    const int sumOfMax = getSumOfMatrixMax(matrix);

    printf("\nThe sum of matrix's maximum values of each row: %d\n", sumOfMax);

    return 0;
}
