#include <stdio.h>

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
 * @brief Получить след матрицы.
 * @details След матрицы - это сумма элементов на ее главной диагонали.
 * @param matrix Матрица, след которой необходимо получить.
 * @return Искомый след матрицы.
 */
int getMatrixTrace(const int matrix[SQ_MATRIX_SIZE][SQ_MATRIX_SIZE]) {
    int trace = 0;
    for (size_t i = 0; i < SQ_MATRIX_SIZE; ++i) {
        trace += matrix[i][i];
    }
    return trace;
}

int main(void) {
    int matrix[SQ_MATRIX_SIZE][SQ_MATRIX_SIZE];
    fillSquareMatrix(matrix);

    const int trace = getMatrixTrace(matrix);

    printf("\nThe matrix trace: %d\n", trace);

    return 0;
}
