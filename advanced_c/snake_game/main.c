#include "properties.h"
#include "logic.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

/**
 * @brief Выполнить одну итерацию обновления логики.
 * @param snake Змейка, состояние которой будет обновлено.
 */
void update(snake_type *snake) {
    moveSnake(snake);
}

/**
 * @brief Выполнить одну итерацию рисования.
 * @param snake Змейка для отрисовки.
 */
void draw(const snake_type *snake) {
    drawSnake(snake);
    refresh();
}

/**
 * @brief Основная функция приложения.
 * @retval 0 Приложение завершило работу в штатном режиме.
 * @retval 1 Приложение завершило работу с ошибкой инициализации змейки.
 */
int main() {
    snake_type *snake = (snake_type *) malloc(sizeof(snake_type));
    initSnake(snake);
    if (!snake->isInitialized) {
        return 1;
    }
    initWindow();

    clock_t iterBegin = clock();
    //! TODO: Позже скорректировать условие цикла.
    while (true) {
        const clock_t iterNow = clock();
        const float iterDuration = ((float)(iterNow - iterBegin) / CLOCKS_PER_SEC);
        if (iterDuration < UPDATE_TIMEOUT_SEC) {
            continue;
        }
        update(snake);
        draw(snake);
        iterBegin = clock();
    }

    free(snake);
    snake = NULL;
    closeWindow();

    return 0;
}
