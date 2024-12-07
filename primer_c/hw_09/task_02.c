#include <stdio.h>
#include <stdbool.h>

//! Характерный размер шахматной доски.
#define CHESS_BOARD_SIZE 8
//! Допустимые буквенные координаты шахматной ячейки.
#define CHESS_ALPHA_COORD "ABCDEFGH"
//! Допустимые цифровые координаты шахматной ячейки.
#define CHESS_DIGIT_COORD "12345678"

/**
 * @brief Инициализировать шахматную доску.
 * @details Отмечает черные ячейки флагом true, а белые - false.
 * @param chessBoard Шахматная доска для инициализации.
 */
void initChessBoard(bool chessBoard[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE]) {
    for (size_t i = 0; i < CHESS_BOARD_SIZE; ++i) {
        size_t blackRemainder = (i % 2 == 0) ? 0 : 1;
        for (size_t j = 0; j < CHESS_BOARD_SIZE; ++j) {
            chessBoard[i][j] = (j % 2 == blackRemainder) ? true : false;
        }
    }
}

/**
 * @brief Проверить корректность координат шахматной ячейки.
 * @details Координаты считаются корректными, если первый символ -
 * буква из диапазона A..H, второй - цифра из диапазона 1..8.
 * @param coords Координаты шахматной ячейки в формате буква-цифра.
 * @return true - координаты шахматной ячейки корректны, false - иначе.
 */
bool checkCoords(const char coords[2]) {
    bool isAlpha = false;
    bool isDigit = false;
    for (size_t i = 0; i < CHESS_BOARD_SIZE; ++i) {
        if (coords[0] == CHESS_ALPHA_COORD[i]) {
            isAlpha = true;
        }
        if (coords[1] == CHESS_DIGIT_COORD[i]) {
            isDigit = true;
        }
    }
    return (isAlpha && isDigit);
}

/**
 * @brief Конвертировать координаты шахматной ячейки из формата буква-цифра в набор индексов.
 * @param coords Координаты шахматной ячейки в формате буква-цифра.
 * @param row Индекс шахматной ячейки, соответствующий буквенной координате.
 * @param column Индекс шахматной ячейки, соответствующий цифровой координате.
 */
void convertCoordsIntoIdx(const char coords[2], size_t *row, size_t *column) {
    for (size_t i = 0; i < CHESS_BOARD_SIZE; ++i) {
        if (coords[0] == CHESS_ALPHA_COORD[i]) {
            *row = i;
        }
        if (coords[1] == CHESS_DIGIT_COORD[i]) {
            *column = i;
        }
    }
}

/**
 * @brief Вывести на экран цвет шахматной ячейки.
 * @param chessBoard Шахматная доска.
 * @param row Индекс шахматной ячейки, соответствующий буквенной координате.
 * @param column Индекс шахматной ячейки, соответствующий цифровой координате.
 */
void printChessCellColor(const bool chessBoard[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE],
        const size_t row, const size_t column) {
    printf("\nThe color of the chess cell: ");
    if (chessBoard[row][column]) {
        printf("BLACK\n");
    } else {
        printf("WHITE\n");
    }
}

int main(void) {
    bool chessBoard[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];
    initChessBoard(chessBoard);

    char coords[2];
    printf("Input a coordinates of the chess cell:\n");
    scanf("%2s", coords);

    if (!checkCoords(coords)) {
        printf("\nInterrupting: incorrect coordinates of the chess cell!\n");
        return 1;
    }

    size_t row = 0;
    size_t column = 0;
    convertCoordsIntoIdx(coords, &row, &column);

    printChessCellColor(chessBoard, row, column);

    return 0;
}
