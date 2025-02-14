#include "properties.h"
#include "logic.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

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

    state status = state_process;
    clock_t iterBegin = clock();
    while (status == state_process) {
        const clock_t iterNow = clock();
        const float iterDuration = ((float)(iterNow - iterBegin) / CLOCKS_PER_SEC);
        if (iterDuration < UPDATE_TIMEOUT_SEC) {
            continue;
        }
        status = update(snake);
        draw(snake);
        iterBegin = clock();
    }

    free(snake);
    snake = NULL;
    closeWindow();

    return 0;
}
