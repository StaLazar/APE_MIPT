#pragma once

//! Клавиша завершения игры.
#define EXIT_KEY KEY_F(10)

//! Количество обновлений логики в секунду.
#define UPS 10U
//! Период обновления логики в секундах.
#define UPDATE_TIMEOUT_SEC (1.F / UPS)

//! Символ-заполнитель для головы змейки.
#define BODY_HEAD '0'
//! Символ-заполнитель для хвоста змейки.
#define BODY_TAIL 'O'
//! Пустой символ-заполнитель.
#define BODY_IDLE ' '

//! Минимальный размер хвоста змейки.
#define MIN_TAIL_SIZE 3UL
//! Максимальный размер хвоста змейки.
#define MAX_TAIL_SIZE 10UL

//! Начальная координата Y змейки.
#define START_COORD_Y (getmaxy(stdscr) / 2)
//! Начальная координата X змейки.
#define START_COORD_X (getmaxx(stdscr) / 2)
