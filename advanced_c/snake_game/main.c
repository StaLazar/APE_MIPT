#include "properties.h"
#include "logic.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

/**
 * @brief Макрос завершения игры.
 * @param[out] ptr Указатель на объект, из-под которого нужно высвободить память.
 */
#define END_GAME(ptr) \
    if ((ptr) != NULL) { \
        free((ptr)); \
        (ptr) = NULL; \
    } \
    closeWindow();

/**
 * @brief Основная функция приложения.
 * @retval 0 Приложение завершило работу в штатном режиме.
 * @retval 1 Приложение завершило работу с ошибкой инициализации змейки.
 */
int main() {
    initWindow();
    snake_type *snake = (snake_type *) malloc(sizeof(snake_type));
    initSnake(snake);
    if (!snake->isInitialized) {
        END_GAME(snake)
        return 1;
    }

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

    END_GAME(snake)
    return 0;
}
